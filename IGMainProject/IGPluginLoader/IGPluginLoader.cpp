#include "IGPluginManager.h"
#include <thread>
#include <chrono>

void PrintInfo()
{
	printf("\n");	
	printf("**************************************************\n");	
	printf("*                                                *\n");
	printf("*               Plugin App Server                *\n");
	printf("*                                                *\n");
	printf("**************************************************\n");	
}

void ConfigParam(int argc, char *argv[])
{
	// argv[0] : filepath
	// argv[1] : server name
	// argv[2] : server Id (to do ...)

	std::string param = "";
	for (int i = 0; i < argc; i++)
	{
		param = argv[i];
		if (param.find("Server=") != std::string::npos)
		{
			param.erase(0, sizeof("Server=")-1);
			IGPluginManager::Instance().SetAppName(param.c_str());
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	PrintInfo();
	ConfigParam(argc, argv);

	IGPluginManager::Instance().Awake();
	IGPluginManager::Instance().Init();
	IGPluginManager::Instance().AfterInit();	
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		IGPluginManager::Instance().Update();
	}

	IGPluginManager::Instance().Finalize();

	return 0;
}
