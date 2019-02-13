#ifndef IG_INETOBJECT_H
#define IG_INETOBJECT_H

class IGNetInterface;

class IGNetObject
{
public:
	IGNetObject(IGNetInterface *pIGINet, int sockfd, sockaddr_in &addr, void *pBev)
		: m_StrBuff(""), m_IPAddr(""), m_UserData(pBev), m_sockfd(sockfd), m_pNet(pIGINet) {
	}
	virtual ~IGNetObject() {}

	inline IGNetInterface *GetNetPtr() 
	{ 
		return m_pNet;
	}

	inline void *GetUserData() 
	{ 
		return m_UserData; 
	}

	inline int GetFD()
	{
		return m_sockfd;
	}

	inline int AddBuff(const char *str, size_t len)
	{
		m_StrBuff.append(str, len);
		return (int)m_StrBuff.length();
	}	

	inline const char* GetBuff()
	{
		return m_StrBuff.c_str();
	}
	
	inline int GetBuffLen()
	{
		return m_StrBuff.length();
	}

private:
	std::string m_StrBuff;
	std::string m_IPAddr;
	void *m_UserData;
	int m_sockfd;

	IGNetInterface* m_pNet;
};

#endif // IG_INETOBJECT_H
