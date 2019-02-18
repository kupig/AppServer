#include "IGNetManager.h"
#include <string.h>

IGNetManager::IGNetManager()
	: IGNetInterface(), mEventBase(NULL)
	, mListener(NULL)
{
	mNetObjectMap.clear();
	mWillCloseNetObjectVec.clear();
}

IGNetManager::~IGNetManager()
{
}

void 
IGNetManager::InitClient(std::string ip, int port)
{
	struct sockaddr_in addr;
	struct bufferevent *bufevent = NULL;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if (evutil_inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0)
	{
		printf("inet_pton");
		return;
	}	
	
	mEventBase = event_base_new();
	if (mEventBase == NULL)
	{
		printf("Failed to call event_base_new(). \n");
		return;
	}

	bufevent = bufferevent_socket_new(mEventBase, -1, BEV_OPT_CLOSE_ON_FREE);	
	if (bufevent == NULL)
	{
		printf("Failed to call bufferevent_socket_new(). \n");
		return;
	}

	int ret = bufferevent_socket_connect(bufevent, (struct sockaddr *)&addr, sizeof(addr));
	if (ret != 0)
	{
		printf("Failed to call bufferevent_socket_connect(). \n");
		return;
	}

	int sockfd = bufferevent_getfd(bufevent);
	IGNetObject *pNetObject = new IGNetObject(this, sockfd, addr, bufevent);
	bool success = AddNetObject(sockfd, pNetObject);
	if (!success)
	{
		printf("Failed to call AddNetObject().\n");
		return;
	}

	bufferevent_setcb(bufevent, ReadCB, WriteCB, EventCB, pNetObject);
	bufferevent_enable(bufevent, EV_READ|EV_WRITE);
}

bool
IGNetManager::InitServer(int port)
{	
	mEventBase = event_base_new();
	if (!mEventBase)
	{
		fprintf(stderr, "Failed to call event_base_new() function.\n");
		return false;
	}
	
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	printf("Server start with %d\n", port);

	mListener = evconnlistener_new_bind(
			mEventBase, ListenCallBack, (void *)this,
		   	LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
			(struct sockaddr *)&addr, sizeof(addr));

	if (!mListener)
	{
		fprintf(stderr, "Failed to create a listener! \n");
		return false;
	}

	return true;
}

bool
IGNetManager::SendMessage(int sockfd, const char *msg, size_t len)
{
	bool ret = false;

	NetObjectMap::iterator it= mNetObjectMap.find(sockfd);
	if (it != mNetObjectMap.end())
	{
		IGNetObject *pNetObject = (IGNetObject *)it->second;
		if (pNetObject == NULL)
		{
			printf("Failed to get sockfd(%d) in SendMessage(). \n", sockfd);
		}
		else
		{
			bufferevent *bev = (bufferevent *)pNetObject->GetUserData();
			if (bev != NULL)
			{
				bufferevent_write(bev, msg, len);
			}
			ret = true;
		}
	}

	return ret;
}

bool 
IGNetManager::AddNetObject(int socketfd, IGNetObject* pNetObject)
{
	return mNetObjectMap.insert(NetObjectMap::value_type(socketfd, pNetObject)).second;
}


bool 
IGNetManager::CloseAllSocket()
{
	NetObjectMap::iterator it = mNetObjectMap.begin();
	for (; it != mNetObjectMap.end(); it++) 
	{
		//size_t fd = it->first;
		IGNetObject *pNetObject = it->second;
		struct bufferevent *bev = (struct bufferevent *)pNetObject->GetUserData();	
		bufferevent_free(bev);
		mNetObjectMap.erase(it);
	}

	return true;
}

void
IGNetManager::Update()
{
	RemoveNetObject();

	if (mEventBase)
	{
		event_base_loop(mEventBase, EVLOOP_ONCE | EVLOOP_NONBLOCK);
	}
}

void
IGNetManager::Finalize()
{
	CloseAllSocket();

	if (mListener)
	{
		evconnlistener_free(mListener);
		mListener = NULL;
	}

	if (mEventBase)
	{
		event_base_free(mEventBase);
		mEventBase = NULL;
	}
}

void
IGNetManager::CloseNetObject(int sockfd)
{
	NetObjectMap::iterator it= mNetObjectMap.find(sockfd);	
	if (it != mNetObjectMap.end())
	{
		IGNetObject *pNetObject = it->second;
		if (pNetObject)
		{
			// ERROR LOG
			return;
		}
			
			
		struct bufferevent *bev = (struct bufferevent *)pNetObject->GetUserData();
		bufferevent_free(bev);
	
		mNetObjectMap.erase(it);

		delete pNetObject;
		pNetObject = NULL;
	}	
}

void
IGNetManager::RemoveNetObject()
{
	for (size_t i = 0; i < mWillCloseNetObjectVec.size(); i++)
	{
		int sockfd = mWillCloseNetObjectVec[i];
		CloseNetObject(sockfd);
	}

	mWillCloseNetObjectVec.clear();
}

void
IGNetManager::ListenCallBack(struct evconnlistener* listener
				, evutil_socket_t fd, struct sockaddr* sa
				, int socklen, void* user_data)
{
	IGNetManager *pIGNetManager = (IGNetManager *)user_data;
	struct event_base *eventBase = pIGNetManager->mEventBase;		
	struct bufferevent *bev = bufferevent_socket_new(eventBase, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev)
	{
		fprintf(stderr, "Failed to get buffer event.\n");
		return;
	}
	
	struct sockaddr_in *pAddr = (sockaddr_in *)sa;
	IGNetObject *pNetObject = new IGNetObject(pIGNetManager, fd, *pAddr, bev);
	IGNetInterface *pNet = pNetObject->GetNetPtr();
	if (!pNet)
	{
		return;
	}
	pNet->AddNetObject(fd, pNetObject);

	bufferevent_setcb(bev, ReadCB, WriteCB, EventCB, (void *)pNetObject);
	bufferevent_enable(bev, EV_READ | EV_WRITE | EV_CLOSED | EV_TIMEOUT);

	EventCB(bev, BEV_EVENT_CONNECTED, (void *)pNetObject);	
}

void 
IGNetManager::ReadCB(struct bufferevent *bev, void *user_data)
{
	IGNetObject *pNetObject = (IGNetObject *)user_data;
	if (!pNetObject)
	{
		return;
	}	

	struct evbuffer *input = bufferevent_get_input(bev);
	if (!input)
	{
		return;
	}

	size_t len = evbuffer_get_length(input);
	unsigned char *pData = evbuffer_pullup(input, len);
	pNetObject->AddBuff((const char *)pData, len);
	evbuffer_drain(input, len);

	// 临时测试, 未经过打包处理.
	// IGNetManager *pNetManager = (IGNetManager *)pNetObject->GetNetPtr(); 
	// pNetManager->mReceiveFunc(pNetObject->GetFD(), 0, pNetObject->GetBuff(), pNetObject->GetBuffLen());
	// pNetObject->RemoveBuff(0, pNetObject->GetBuffLen());

	// TO DO ...
	// 拆分消息
}

void
IGNetManager::WriteCB(struct bufferevent *bev, void *user_data)
{
	// nothing to do , use for sendMsg function .
}

void
IGNetManager::EventCB(struct bufferevent *bev, short events, void *user_data)
{	
	IGNetObject *pNetObject = (IGNetObject *)user_data;
	IGNetManager *pNetManager = (IGNetManager *)pNetObject->GetNetPtr();

	pNetManager->mEventFunc(pNetObject->GetFD(), IG_NET_EVENT(events), pNetManager);

	if (events & BEV_EVENT_CONNECTED)
	{
		printf("Hey! socket connected.\n");	
	}
	else
	{
		pNetManager->CloseNetObject(pNetObject->GetFD());
	}
}





