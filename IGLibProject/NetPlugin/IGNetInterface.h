#ifndef __IG_INET_H__
#define __IG_INET_H__

#include <string>

#pragma pack(push, 1)

#include "../../IGMainProject/Dependencies/libevent/event2/event.h"
#include "../../IGMainProject/Dependencies/libevent/event2/listener.h"
#include "../../IGMainProject/Dependencies/libevent/event2/bufferevent.h"
#include "../../IGMainProject/Dependencies/libevent/event2/buffer.h"
#include "../../IGMainProject/Dependencies/libevent/event2/util.h"
#include "IGNetObject.h"

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
