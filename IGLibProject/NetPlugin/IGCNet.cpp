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


	return true;
}

void
IGCNet::SendMessage()
{
}

void
IGCNet::ListenCallBack(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sa, int socklen, void* user_data)
{
}
