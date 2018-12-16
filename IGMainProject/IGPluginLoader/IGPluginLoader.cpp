#include "IGPluginManager.h"

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
	// argv[2] : server Id

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

	printf("start parameter: %s\n\n", param.c_str());

	}

int main(int argc, char* argv[])
{
	PrintInfo();
	ConfigParam(argc, argv);

	IGPluginManager::Instance().Awake();
	IGPluginManager::Instance().Init();
	
	//while (1)
	{
		//IGPluginManager::Instance().Update();

	}

	IGPluginManager::Instance().Finalize();

	return 0;
}
