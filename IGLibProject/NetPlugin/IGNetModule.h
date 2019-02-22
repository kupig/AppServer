#ifndef IG_NETMOUDLE_H
#define IG_NETMOUDLE_H

#include "../../IGMainProject/IGPluginMoudle/IGINetMoudle.h"
#include "../../IGMainProject/IGInterface/IGIPluginManager.h"
#include "IGNetManager.h"

class IGNetMoudle 
	: public IGINetMoudle
{
public:
	IGNetMoudle(IGIPluginManager *p);
	virtual ~IGNetMoudle();	

	virtual bool Awake();
	virtual bool Init();
	virtual bool AfterInit();
	virtual bool Update();
	virtual bool Finalize();

	virtual void CreateServerNet(int port);
	virtual void RemoveServerNet();

	virtual bool ReMsgCB(int msgId, NET_RECIEVE_FUNCTION_PTR &cb);
protected:
	void OnReceiveNetPack(int sockfd, int msgId, const char* msg, unsigned int len);
	void OnEventNetPack(int sockfd, IG_NET_EVENT event, IGNetInterface* pINet);

private:
	IGNetManager *m_pNetMngr;
	//std::map<int,>
};

#endif // IG_NETMOUDLE_H
