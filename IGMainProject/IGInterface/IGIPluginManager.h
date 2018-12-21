#ifndef IG_IPLUGIN_MANAGER_H
#define IG_IPLUGIN_MANAGER_H

#include "IGIPlugin.h"
#include <typeinfo>
#include <type_traits>

class IGIPluginManager
{
public:
	virtual bool Awake() { return true; }	
	virtual bool Init() {return true;}
	virtual bool AfterInit() {return true;}
	virtual bool Update() {return true;}
	virtual bool Finalize() {return true;}

	virtual bool RegisterPlugin(IGIPlugin *pPlugin) = 0; 
	virtual bool UnregisterPlugin(IGIPlugin *pPlugin) = 0;

	virtual bool AddMoudle(const std::string &moudleName, IGIMoudle *pMoudle) = 0;
	virtual bool RemoveMoudle(const std::string &moudleName) = 0;

	virtual IGIPlugin *FindPlugin(const std::string &pluginName) = 0;
	virtual IGIMoudle *FindMoudle(const std::string &moudleName) = 0; 

	template<typename B, typename S>
	S *FindMoudle()
	{
		if (std::is_base_of<B, S>::value == true)
		{
			B* base = FindMoudle(typeid(S).name());
			S* sub = dynamic_cast<S *>(base);
			//assert(sub != NULL);
			return sub;
		}
		return NULL;
	}
};

#endif // IG_IPLUGIN_MANAGER_H
