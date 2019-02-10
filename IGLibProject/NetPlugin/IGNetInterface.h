#ifndef __IG_INET_H__
#define __IG_INET_H__

#include <string>
#include <functional>

#pragma pack(push, 1)

#include "../../IGMainProject/Dependencies/libevent/event2/event.h"
#include "../../IGMainProject/Dependencies/libevent/event2/listener.h"
#include "../../IGMainProject/Dependencies/libevent/event2/bufferevent.h"
#include "../../IGMainProject/Dependencies/libevent/event2/buffer.h"
#include "../../IGMainProject/Dependencies/libevent/event2/util.h"
#include "IGNetObject.h"

enum IG_NET_EVENT
{
	IG_NET_EVENT_EOF = 0x10,
	IG_NET_EVENT_ERROR = 0X20,
	IG_NET_EVENT_TIMEOUT = 0x40,
	IG_NET_EVENT_CONNECTED = 0x80,
};

typedef std::function<void(int sockfd, int msgId, const char *msg, unsigned int len)> NET_RECIEVE_FUNCTION;
typedef std::function<void(int sockfd, IG_NET_EVENT event, IGNetInterface*)> NET_EVENT_FUNCTION;

class IGNetInterface
{
public:	
	IGNetInterface() {}
	virtual ~IGNetInterface() {}
	
	virtual void InitClient() = 0;
	virtual bool InitServer(int port) = 0;	

	virtual void SendMessage() = 0;
	virtual bool AddNetObject(int socketfd, IGNetObject* pNetObject) = 0;
	virtual bool CloseAllSocket() = 0;

	virtual void Update() = 0;
	virtual void Finalize() = 0;
};

#pragma pack(pop)

#endif //__IG_INET_H__
