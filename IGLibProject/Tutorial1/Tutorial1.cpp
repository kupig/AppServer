#include "Tutorial1.h"
#include <stdio.h>
#include "../../IGMainProject/IGCommon/IGPlatform.h"
#include "Tutorial1Moudle1.h"

extern "C" void LibPluginStart(IGIPluginManager *pPluginManager)
{
	printf("\ncreate and register Tutorial1 in pPluginManager.\n");
	CREATE_PLUGIN_OBJECT(pPluginManager, Tutorial1);
}

extern "C" void LibPluginStop(IGIPluginManager *pPluginManager)
{
	printf("\nstop and register Tutorial1 in pPluginManager.\n");
	DESTROY_PLUGIN_OBJECT(pPluginManager, Tutorial1);
}

Tutorial1::Tutorial1(IGIPluginManager* p)
{
	pPluginManager = (void *)p;
}

Tutorial1::~Tutorial1()
{
}

void
Tutorial1::InstallMoudle()
{
	PRINT_FUNC();
	REGISTER_MOUDLE(pPluginManager, IGITutorial1Moudle1, Tutorial1Moudle1);
}

void
Tutorial1::UninstallMoudle()
{
	PRINT_FUNC();
	UNREGISTER_MOUDLE(pPluginManager, IGITutorial1Moudle1, Tutorial1Moudle1);
}

std::string
Tutorial1::GetPluginName()
{
	return PLUGIN_NAME(Tutorial1);
}
