#ifndef IG_PLUGIN_MANAGER
#define IG_PLUGIN_MANAGER

#include <map>
#include "../IGCommon/IGSingleton.h"
#include "../IGCommon/IGHelperHandle.h"
#include "../IGInterface/IGIPluginManager.h"
#include "IGDynamicLib.h"

class IGPluginManager 
	: public IGIPluginManager
	, public IGSingleton<IGPluginManager>
{
public:
	IGPluginManager();
	virtual ~IGPluginManager();

	virtual bool Awake();
	virtual bool Init();
	virtual bool AfterInit();
	virtual bool Update();
	virtual bool Finalize();

	bool SetAppName(const char *appName);
	
	virtual bool RegisterPlugin(IGIPlugin *pPlugin);
	virtual bool UnregisterPlugin(IGIPlugin *pPlugin);
	
	virtual bool AddMoudle(const std::string &moudleName, IGIMoudle *pMoudle);
	virtual bool RemoveMoudle(const std::string &moudleName);

	virtual IGIPlugin *FindPlugin(const std::string &pluginName);
	virtual IGIMoudle *FindMoudle(const std::string &moudleName);

protected:
	bool LoadPluginConfig();
	bool LoadPluginLibrary();
	bool UnLoadPluginLibrary();

private:
	std::string mAppName;

	typedef std::map<std::string, bool> PluginNameMap;
	typedef std::map<std::string, IGDynamicLib*> PluginLibMap;
	typedef std::map<std::string, IGIPlugin*> PluginInstanceMap;
	typedef std::map<std::string, IGIMoudle*> MoudleInstanceMap;

	PluginNameMap mPluginNameMap;
	PluginLibMap mPluginLibMap; 			// useful for load *.so
	PluginInstanceMap mPluginInstanceMap; 	// useful for load *PluginInstance
	MoudleInstanceMap mMoudleInstanceMap;	// useful for load *MoudleInstacne

	
};

#endif //IG_PLUGIN_MANAGER
