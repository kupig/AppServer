#ifndef IG_CNET_H
#define IG_CNET_H

#include "IGNetInterface.h"
#include <map>
#include <vector>

#pragma pack(push, 1)

class IGNetManager : public IGNetInterface
{
public:
	IGNetManager();
	template<typename HandleClassPtr>
	IGNetManager(HandleClassPtr *pThis 
		, void (HandleClassPtr::*handleReceive)(int, int, const char*, unsigned int)
		, void (HandleClassPtr::*handleEvent)(int, IG_NET_EVENT, IGNetInterface*))
	{
		mEventBase = NULL;
		mListener = NULL;	
		mReceiveFunc = std::bind(handleReceive, pThis, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
		mEventFunc = std::bind(handleEvent, pThis, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}	
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
	
	NET_RECIEVE_FUNCTION mReceiveFunc;
	NET_EVENT_FUNCTION mEventFunc;
};
#pragma pack(pop)

#endif //IG_CNET_H
