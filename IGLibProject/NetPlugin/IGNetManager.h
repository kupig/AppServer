#ifndef IG_CNET_H
#define IG_CNET_H

#include "../../IGMainProject/IGCommon/IGINet.h"
#include "../../IGMainProject/Dependencies/libevent/event2/util.h"
#include "../../IGMainProject/Dependencies/libevent/event2/event.h"
#include "../../IGMainProject/Dependencies/libevent/event2/listener.h"
#include "../../IGMainProject/Dependencies/libevent/event2/bufferevent.h"
#include "../../IGMainProject/Dependencies/libevent/event2/buffer.h"
#include <map>
#include <vector>

#pragma pack(push, 1)

class IGNetManager : public IGINet
{
public:
	IGNetManager();
	virtual ~IGNetManager();

	virtual void InitClient();
	virtual bool InitServer(int port);
	virtual void SendMessage();
	virtual bool AddNetObject(int socketfd, IGNetObject* pNetObject);
	virtual bool CloseAllSocket();

	virtual void Update();
	virtual void Finalize();

public:
	void CloseNetObject(int sockfd);
	void RemoveNetObject();

public:
	static void ListenCallBack(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sa, int socklen, void* user_data);
	static void ReadCB(struct bufferevent *bev, void *user_data);
	static void WriteCB(struct bufferevent *bev, void *user_data);
	static void EventCB(struct bufferevent *bev, short events, void *user_data);

private:
	struct event_base *mEventBase;
	struct evconnlistener *mListener;

	typedef std::map<int, IGNetObject*> NetObjectMap;
	typedef std::vector<int> NetObjectVec;

	NetObjectMap mNetObjectMap;
	NetObjectVec mWillCloseNetObjectVec;
};
#pragma pack(pop)

#endif //IG_CNET_H
