#ifndef IG_IPLUGIN_MANAGER_H
#define IG_IPLUGIN_MANAGER_H

#include "IGIPlugin.h"

class IGIPluginManager
{
public:
	virtual bool Awake() { return true; }	
	virtual bool Init() {return true;}
	virtual bool AfterInit() {return true;}
	virtual bool CheckConfig() {return true;}
	virtual bool ReadyExecute() {return true;}
	virtual bool Update() {return true;}
	virtual bool BeforeShut() {return true;}
	virtual bool Shut() {return true;}
	virtual bool Finalize() {return true;}

	virtual bool RegisterPlugin(IGIPlugin *pPlugin) = 0; 
	virtual bool UnregisterPlugin(IGIPlugin *pPlugin) = 0;
	virtual IGIPlugin *FindPlugin(std::string pluginName) = 0;
};

#endif // IG_IPLUGIN_MANAGER_H
