#ifndef __IG_INET_H__
#define __IG_INET_H__

#include <string>

#pragma pack(push, 1)

#include "../Dependencies/libevent/event2/util.h"

class IGINet;

class IGNetObject
{
public:
	IGNetObject(IGINet *pIGINet, int sockfd, sockaddr_in &addr, void *pBev)
	{
	}
	virtual ~IGNetObject() {}

	
public:
	std::string mStrBuff;
	std::string mIPAddr;
	int	mPort;
	void *mUserData;
};

class IGINet
{
public:	
	IGINet() {}
	virtual ~IGINet() {}
	
	virtual void InitClient() = 0;
	virtual bool InitServer(int port) = 0;	

	virtual void SendMessage() = 0;
};

#pragma pack(pop)

#endif //__IG_INET_H__
