#include "IGPluginManager.h"
#include "../IGCommon/IGPlatform.h"
#include "../Dependencies/rapidxml/rapidxml.hpp"
#include "../Dependencies/rapidxml/rapidxml_iterators.hpp"
#include "../Dependencies/rapidxml/rapidxml_print.hpp"
#include "../Dependencies/rapidxml/rapidxml_utils.hpp"

#define FOR_EACH_MAP(FUNCTION)		\
	PluginInstanceMap::iterator it = mPluginInstanceMap.begin();	\
	for (; it != mPluginInstanceMap.end(); it++)					\
	{ 																\
		it->second->FUNCTION();										\
	}

typedef void (*pFunc)(IGIPluginManager *pPluginManager);

IGPluginManager::IGPluginManager()
	: mAppName("")
{
	mPluginNameMap.clear();
	mPluginLibMap.clear();	
	mMoudleInstanceMap.clear();
}

IGPluginManager::~IGPluginManager()
{
	
}

bool 
IGPluginManager::Awake()
{
	PRINT_FUNC();
	LoadPluginConfig();
	LoadPluginLibrary();
	FOR_EACH_MAP(Awake);	

	return true;
}

bool 
IGPluginManager::Init()
{
	PRINT_FUNC();
	FOR_EACH_MAP(Init);
	return true;	
}

bool
IGPluginManager::AfterInit()
{
	PRINT_FUNC();
	FOR_EACH_MAP(AfterInit);
	return true;
}

bool
IGPluginManager::Update()
{
	PRINT_FUNC();
	FOR_EACH_MAP(Update);
	return true;
}

bool 
IGPluginManager::Finalize()
{
	PRINT_FUNC();
	FOR_EACH_MAP(Finalize);
	UnLoadPluginLibrary();
	return true;
}

bool
IGPluginManager::SetAppName(const char *appName)
{
	if (!appName)
	{
		return false;
	}

	mAppName = appName;	
#if IG_PLATFORM == IG_PLATFORM_LINUX
	prctl(PR_SET_NAME, ("IG" + mAppName).c_str());
#endif
	return true;
}

bool 
IGPluginManager::RegisterPlugin(IGIPlugin *pPlugin)
{
	bool ret = false;

	if (pPlugin != NULL) 
	{
		std::string pluginName = pPlugin->GetPluginName();
		
		if (mPluginInstanceMap.find(pluginName) == mPluginInstanceMap.end())
		{
			mPluginInstanceMap.insert(make_pair(pluginName, pPlugin));
			pPlugin->InstallMoudle();
			ret = true;
		}
		else
		{
			// ASSERT TO DO ...
		}
	}

	return ret;	
}

bool 
IGPluginManager::UnregisterPlugin(IGIPlugin *pPlugin)
{
	bool ret = false;
	
	if (pPlugin)
	{
		std::string pluginName = pPlugin->GetPluginName();
		
		PluginInstanceMap::iterator it = mPluginInstanceMap.find(pluginName);
		if (it != mPluginInstanceMap.end())
		{
			it->second->UninstallMoudle();
			XDELETE(it->second);
			it->second = NULL;
			mPluginInstanceMap.erase(it);
			
			ret = true;
		}
	}	

	return ret;
}

bool
IGPluginManager::AddMoudle(const std::string &moudleName, IGIMoudle *pMoudle)
{
		bool ret = false;

		MoudleInstanceMap::iterator it = mMoudleInstanceMap.find(moudleName);	
		if (it != mMoudleInstanceMap.end())
		{
			// ERROR_LOG OR ASSERT
		}
		else
		{
			mMoudleInstanceMap.insert(MoudleInstanceMap::value_type(moudleName, pMoudle));
			ret = true;
		}

		return ret;
}

bool
IGPluginManager::RemoveMoudle(const std::string &moudleName)
{
	bool ret = false;

	MoudleInstanceMap::iterator it = mMoudleInstanceMap.find(moudleName);	
	if (it != mMoudleInstanceMap.end())
	{
		mMoudleInstanceMap.erase(it);
		
		// it->second has been delete in "UNREGISTER_MOUDLE"
	}

	return ret;
}

IGIPlugin *
IGPluginManager::FindPlugin(const std::string &pluginName)
{
	PluginInstanceMap::iterator it = mPluginInstanceMap.find(pluginName);
	if (it != mPluginInstanceMap.end())
	{
		return it->second;
	}

	return NULL;
}

IGIMoudle *
IGPluginManager::FindMoudle(const std::string &moudleName)
{
	std::string subClassName = moudleName.substr(2);

	MoudleInstanceMap::iterator it = mMoudleInstanceMap.find(subClassName);
	if (it != mMoudleInstanceMap.end())
	{
		return it->second;
	}

	return NULL;
}

bool
IGPluginManager::LoadPluginConfig()
{
	std::string filePath = "./Config/PluginConfig.xml";
	std::string content;
	bool success = HelperHandle::GetFileContent(filePath, content);
	if (!success) 
	{
		// ERR_LOG or ASSERT
		return false;
	}
	
	rapidxml::xml_document<> doc;
	doc.parse<0>((char *)content.c_str());	
	rapidxml::xml_node<> *pRoot = doc.first_node();
	rapidxml::xml_node<> *pAppName = pRoot->first_node(mAppName.c_str());
	if (!pAppName)
	{
		// ERR_LOG or ASSERT
		return false;
	}

	for (rapidxml::xml_node<> *pPlugin = pAppName->first_node("Plugin");
			pPlugin != NULL; pPlugin = pPlugin->next_sibling("Plugin"))
	{
		std::string value = pPlugin->first_attribute("Name")->value();
		printf("%s\n", value.c_str());
		mPluginNameMap.insert(PluginNameMap::value_type(value, false));
	}	

	return true;
}

bool 
IGPluginManager::LoadPluginLibrary()
{	
	bool bLoad = false;

	for (PluginNameMap::iterator it = mPluginNameMap.begin()
		; it != mPluginNameMap.end(); it++)
	{
		IGDynamicLib *pluginLib = new IGDynamicLib(it->first);
		bLoad = pluginLib->LoadLibrary();
		if (!bLoad)
		{
			// ERR_LOG or ASSERT
			break;
		}

		pFunc pFunction = (void(*)(IGIPluginManager*))pluginLib->GetSymbol("LibPluginStart");
		if (!pFunction)
		{
			break;
		}

		pFunction(this);
		mPluginLibMap.insert(PluginLibMap::value_type(it->first, pluginLib));
	}

	return bLoad;
}

bool
IGPluginManager::UnLoadPluginLibrary()
{
	bool bUnLoad = true;	

	for (PluginNameMap::iterator it_name = mPluginNameMap.begin()
		; it_name != mPluginNameMap.end(); it_name++)
	{
			PluginLibMap::iterator it_lib = mPluginLibMap.find(it_name->first);	
			if (it_lib != mPluginLibMap.end())
			{
				IGDynamicLib *pluginLib = it_lib->second;
				if (!pluginLib)
				{
					// ERR_LOG or ASSERT
					bUnLoad = false;
					break;
				}
				
				pFunc pFunction = (void(*)(IGIPluginManager*))pluginLib->GetSymbol("LibPluginStop");
				if (!pFunction)
				{
					break;
				}

				pFunction(this);			
				pluginLib->UnLoadLibrary();	
				XDELETE(pluginLib);				
			}
	}

	return bUnLoad;
}
