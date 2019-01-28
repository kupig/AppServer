#include "IGNetPlugin.h"
#include <stdio.h>
#include "../../IGMainProject/IGCommon/IGPlatform.h"

extern "C" void LibPluginStart(IGIPluginManager *pPluginManager)
{
	printf("\n** create and register NetPlugin in pPluginManager.\n");	
}

extern "C" void LibPluginStop(IGIPluginManager *pPluginManager)
{
	printf("\n** stop and register NetPlugin in pPluginManager.\n");
}

IGNetPlugin::IGNetPlugin(IGIPluginManager *p)
{
}

IGNetPlugin::~IGNetPlugin()
{
}

void
IGNetPlugin::InstallModule()
{
}

void
IGNetPlugin::UninstallModule()
{
}

std::string
IGNetPlugin::GetPluginName()
{
	return "";
}
