#ifndef IG_CNET_H
#define IG_CNET_H

#include "../../IGMainProject/IGCommon/IGINet.h"
#include "../../IGMainProject/Dependencies/libevent/event2/util.h"
#include "../../IGMainProject/Dependencies/libevent/event2/event.h"
#include "../../IGMainProject/Dependencies/libevent/event2/listener.h"
#include "../../IGMainProject/Dependencies/libevent/event2/bufferevent.h"
#include <map>

#pragma pack(push, 1)

class IGCNet : public IGINet
{
public:
	IGCNet();
	virtual ~IGCNet();

	virtual void InitClient();
	virtual bool InitServer(int port);
	virtual void SendMessage();
	virtual bool AddNetObject(int socketfd, IGNetObject* pNetObject);

public:
	static void ListenCallBack(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sa, int socklen, void* user_data);
	static void ReadCB(struct bufferevent *bev, void *user_data);
	static void WriteCB(struct bufferevent *bev, void *user_data);
	static void EventCB(struct bufferevent *bev, short events, void *user_data);

private:
	struct event_base *mEventBase;
	struct evconnlistener *mListener;

	std::map<int, IGNetObject*> mNetObjectMap;
};
#pragma pack(pop)

#endif //IG_CNET_H
