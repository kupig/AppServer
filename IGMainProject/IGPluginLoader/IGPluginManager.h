#ifndef IG_PLUGIN_MANAGER
#define IG_PLUGIN_MANAGER

#include <map>
#include "../IGCommon/IGSingleton.h"
#include "../IGCommon/IGHelperHandle.h"
#include "IGDynamicLib.h"

class IGPluginManager 
	: public IGSingleton<IGPluginManager>
{
public:
	IGPluginManager();
	virtual ~IGPluginManager();

	virtual bool Awake();
	virtual bool Init();
	virtual bool AfterInit();
	virtual bool CheckConfig();
	virtual bool ReadyExecute();
	virtual bool Update();
	virtual bool BeforeShut();
	virtual bool Shut();
	virtual bool Finalize();

	bool SetAppName(const char *appName);

protected:
	bool LoadPluginConfig();
	bool LoadPluginLibrary();
	bool UnLoadPluginLibrary();

private:
	std::string mAppName;

	typedef std::map<std::string, bool> PluginNameMap;
	typedef std::map<std::string, IGDynamicLib*> PluginLibMap;

	PluginNameMap mPluginNameMap;
	PluginLibMap mPluginLibMap;
};

#endif //IG_PLUGIN_MANAGER
