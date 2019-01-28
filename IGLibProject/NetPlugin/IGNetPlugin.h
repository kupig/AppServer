#ifndef IG_NET_PLUGIN_H
#define IG_NET_PLUGIN_H

#include "../../IGMainProject/IGInterface/IGIPlugin.h"
#include "../../IGMainProject/IGInterface/IGIPluginManager.h"

class IGNetPlugin : public IGIPlugin
{
public:
	IGNetPlugin(IGIPluginManager *p);
	virtual ~IGNetPlugin();

	virtual void InstallModule();
	virtual void UninstallModule();	

	std::string GetPluginName();
};

#endif // IG_NET_PLUGIN_H
