#include "/home/user/Desktop/AppServer/IGLibProject/NetPlugin/IGNetManager.h"
#include <stdio.h>

class TestClient
{
public:
	TestClient() : bConnected(false)
	{
		pNet = new IGNetManager(this, &TestClient::ReceiveHandler, &TestClient::EventHandle);
		pNet->InitClient("127.0.0.1", 8888);
	}

	~TestClient()
	{
		delete pNet;
		pNet = NULL;
	}

	void ReceiveHandler(int sockfd, int msgId, const char *msg, unsigned int len)
	{
	}

	void EventHandle(int sockfd, IG_NET_EVENT event, IGNetInterface *p)
	{
		if (event & IG_NET_EVENT_CONNECTED)
		{
			bConnected = true;
		}
	}

	void Update()
	{
		pNet->Update();
	}

private:
	IGNetInterface *pNet;
	bool bConnected;
};

int main(int argc, char * argv[])
{
	TestClient cli;
	while (1)
	{
		cli.Update();
	}

	return 0;
}
