#include "IGNetPlugin.h"
#include <stdio.h>
#include "../../IGMainProject/IGCommon/IGPlatform.h"
#include "IGNetModule.h"

extern "C" void LibPluginStart(IGIPluginManager *pPluginManager)
{
	printf("\n** create and register NetPlugin in pPluginManager.\n");	
	CREATE_PLUGIN_OBJECT(pPluginManager, IGNetPlugin);
}

extern "C" void LibPluginStop(IGIPluginManager *pPluginManager)
{
	printf("\n** stop and register NetPlugin in pPluginManager.\n");
	DESTROY_PLUGIN_OBJECT(pPluginManager, IGNetPlugin);
}

IGNetPlugin::IGNetPlugin(IGIPluginManager *p)
{
	pPluginManager = p;
}

IGNetPlugin::~IGNetPlugin()
{
}

void
IGNetPlugin::InstallMoudle()
{
	//PRINT_FUNC();
	//REGISTER_MOUDLE(pPluginManager, IGINetMoudle, IGNetMoudle);
}

void
IGNetPlugin::UninstallMoudle()
{
}

std::string
IGNetPlugin::GetPluginName()
{
	return PLUGIN_NAME(IGNetPlugin);
}
