#include "IGNetManager.h"
#include <string.h>

IGNetManager::IGNetManager()
	: mEventBase(NULL)
	, mListener(NULL)
{
	mNetObjectMap.clear();
	mWillCloseNetObjectVec.clear();
}

IGNetManager::~IGNetManager()
{
}

void 
IGNetManager::InitClient()
{
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

void
IGNetManager::SendMessage()
{
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

	// TO DO ...
}

void
IGNetManager::WriteCB(struct bufferevent *bev, void *user_data)
{
}

void
IGNetManager::EventCB(struct bufferevent *bev, short events, void *user_data)
{
}





