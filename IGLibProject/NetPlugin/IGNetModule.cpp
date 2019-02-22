#include "IGNetModule.h"
#include "../../IGMainProject/IGCommon/IGPlatform.h"

IGNetMoudle::IGNetMoudle(IGIPluginManager *p)
	: m_pNetMngr(NULL) 
{
	pPluginManager = p;
}

IGNetMoudle::~IGNetMoudle()
{
	RemoveServerNet();
}

bool
IGNetMoudle::Awake()
{
	PRINT_FUNC();
	return true;
}

bool
IGNetMoudle::Init()
{
	PRINT_FUNC();
	return true;
}

bool
IGNetMoudle::AfterInit()
{
	PRINT_FUNC();
	return true;
}

bool
IGNetMoudle::Update()
{
	if (!m_pNetMngr)
	{
		return false;
	}

	PRINT_FUNC();	
	m_pNetMngr->Update();
	return true;
}

bool
IGNetMoudle::Finalize()
{
	PRINT_FUNC();

	if (!m_pNetMngr)
	{
		return false;
	}

	m_pNetMngr->Finalize();

	return true;
}

void
IGNetMoudle::CreateServerNet(int port)
{
	m_pNetMngr = new IGNetManager(this, &IGNetMoudle::OnReceiveNetPack, &IGNetMoudle::OnEventNetPack);	
	m_pNetMngr->InitServer(port);
}

void
IGNetMoudle::RemoveServerNet()
{
	delete m_pNetMngr;	
	m_pNetMngr = NULL;
}

bool 
IGNetMoudle::ReMsgCB(int msgId, NET_RECIEVE_FUNCTION_PTR &cb)
{
	return true;
}

void
IGNetMoudle::OnReceiveNetPack(int sockfd, int msgId, const char *msg, unsigned int len)
{
}

void
IGNetMoudle::OnEventNetPack(int sockfd, IG_NET_EVENT event, IGNetInterface *pINet)
{
}
