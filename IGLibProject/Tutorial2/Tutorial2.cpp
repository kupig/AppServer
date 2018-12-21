#include "Tutorial2.h"
#include <stdio.h>
#include "../../IGMainProject/IGCommon/IGPlatform.h"
#include "Tutorial2Moudle1.h"

extern "C" void LibPluginStart(IGIPluginManager *pPluginManager)
{
	printf("\ncreate and register Tutorial2 in pPluginManager.\n");
	CREATE_PLUGIN_OBJECT(pPluginManager, Tutorial2);
}

extern "C" void LibPluginStop(IGIPluginManager *pPluginManager)
{
	printf("\nstop and register Tutorial2 in pPluginManager.\n");
	DESTROY_PLUGIN_OBJECT(pPluginManager, Tutorial2);
}

Tutorial2::Tutorial2(IGIPluginManager* p)
{
	pPluginManager = (void *)p;
}

Tutorial2::~Tutorial2()
{
}

void
Tutorial2::InstallMoudle()
{
	PRINT_FUNC();
	REGISTER_MOUDLE(pPluginManager, IGITutorial2Moudle1, Tutorial2Moudle1);
}

void
Tutorial2::UninstallMoudle()
{
	PRINT_FUNC();
	UNREGISTER_MOUDLE(pPluginManager, IGITutorial2Moudle1, Tutorial2Moudle1);
}

std::string
Tutorial2::GetPluginName()
{
	return PLUGIN_NAME(Tutorial2);
}
