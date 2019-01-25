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
		: m_pNet(pIGINet), m_UserData(pBev)
	{
	}
	virtual ~IGNetObject() {}

	inline IGINet *GetNetPtr() 
	{ 
		return m_pNet;
	}
	inline void *GetUserData() 
	{ 
		return m_UserData; 
	}
	inline int AddBuff(const char *str, size_t len)
	{
		m_StrBuff.append(str, len);
		return (int)m_StrBuff.length();
	}	
	
private:
	std::string m_StrBuff;
	std::string m_IPAddr;
	int	m_Port;
	void *m_UserData;

	IGINet* m_pNet;
};

class IGINet
{
public:	
	IGINet() {}
	virtual ~IGINet() {}
	
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
