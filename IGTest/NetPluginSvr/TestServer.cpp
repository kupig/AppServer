#include "../../IGLibProject/NetPlugin/IGNetManager.h"
#include <stdio.h>

class TestServer
{
public:
	TestServer()
	{
		pNet = new IGNetManager(this, &TestServer::ReceiveHandler, &TestServer::EventHandle);
		pNet->InitServer(8888);
	}

	~TestServer()
	{
		delete pNet;
		pNet = NULL;
	}

	void ReceiveHandler(int sockfd, int msgId, const char *msg, unsigned int len)
	{
		printf("receive message: %s\n", msg);
	}

	void EventHandle(int sockfd, IG_NET_EVENT event, IGNetInterface *p)
	{
	}

	void Update()
	{
		pNet->Update();
	}

private:
	IGNetInterface *pNet;
};

int main()
{
	printf("begin...\n");

	TestServer svr;
	while (1)
	{
		svr.Update();
	}	

	printf("end...\n");
	return 0;
}

