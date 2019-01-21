#ifndef IG_CNET_H
#define IG_CNET_H

#include "../../IGMainProject/IGCommon/IGINet.h"
#include "../../IGMainProject/Dependencies/libevent/event2/util.h"
#include "../../IGMainProject/Dependencies/libevent/event2/event.h"
#include "../../IGMainProject/Dependencies/libevent/event2/listener.h"

#pragma pack(push, 1)

class IGCNet : public IGINet
{
public:
	IGCNet();
	virtual ~IGCNet();

	virtual void InitClient();
	virtual bool InitServer(int port);
	virtual void SendMessage();

	static void ListenCallBack(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sa, int socklen, void* user_data);
private:
	struct event_base *mEventBase;
	struct evconnlistener *mListener;
};
#pragma pack(pop)

#endif //IG_CNET_H
