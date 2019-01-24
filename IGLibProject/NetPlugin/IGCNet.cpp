#include "IGCNet.h"
#include <string.h>

IGCNet::IGCNet()
	: mEventBase(NULL)
	, mListener(NULL)
{
}

IGCNet::~IGCNet()
{
}

void 
IGCNet::InitClient()
{
}

bool
IGCNet::InitServer(int port)
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
IGCNet::SendMessage()
{
}

bool 
IGCNet::AddNetObject(int socketfd, IGNetObject* pNetObject)
{
	return mNetObjectMap.insert(std::map<int, IGNetObject*>::value_type(socketfd, pNetObject)).second;
}

void
IGCNet::ListenCallBack(struct evconnlistener* listener
				, evutil_socket_t fd, struct sockaddr* sa
				, int socklen, void* user_data)
{
	IGCNet *pIGCNet = (IGCNet *)user_data;
	struct event_base *eventBase = pIGCNet->mEventBase;		
	struct bufferevent *bev = bufferevent_socket_new(eventBase, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev)
	{
		fprintf(stderr, "Failed to get buffer event.\n");
		return;
	}
	
	struct sockaddr_in *pAddr = (sockaddr_in *)sa;
	IGNetObject *pNetObject = new IGNetObject(pIGCNet, fd, *pAddr, bev);
	IGINet *pNet = pNetObject->GetNetPtr();
	if (!pNet)
	{
		return;
	}
	pNet->AddNetObject(fd, pNetObject);
}

void 
IGCNet::ReadCB(struct bufferevent *bev, void *user_data)
{
}

void
IGCNet::WriteCB(struct bufferevent *bev, void *user_data)
{
}

void
IGCNet::EventCB(struct bufferevent *bev, short events, void *user_data)
{
}





