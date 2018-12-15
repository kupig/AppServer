#include "IGPluginManager.h"
#include "../IGCommon/IGPlatform.h"
#include "../Dependencies/rapidxml/rapidxml.hpp"
#include "../Dependencies/rapidxml/rapidxml_iterators.hpp"
#include "../Dependencies/rapidxml/rapidxml_print.hpp"
#include "../Dependencies/rapidxml/rapidxml_utils.hpp"

typedef void (*pFunc)(void);

IGPluginManager::IGPluginManager()
	: mAppName("")
{
	mPluginNameMap.clear();
	mPluginLibMap.clear();	
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

	return true;
}

bool 
IGPluginManager::Init()
{
	PRINT_FUNC();
	return true;	
}

bool
IGPluginManager::AfterInit()
{
	PRINT_FUNC();
	return true;
}

bool 
IGPluginManager::CheckConfig()
{
	PRINT_FUNC();
	return true;
}

bool
IGPluginManager::ReadyExecute()
{
	PRINT_FUNC();
	return true;
}

bool
IGPluginManager::Update()
{
	PRINT_FUNC();
	return true;
}

bool
IGPluginManager::BeforeShut()
{
	PRINT_FUNC();
	return true;
}

bool 
IGPluginManager::Shut()
{
	PRINT_FUNC();
	return true;
}

bool 
IGPluginManager::Finalize()
{
	PRINT_FUNC();
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

		pFunc pFunction = (void(*)())pluginLib->GetSymbol("func");
		pFunction();
		
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
				
				pluginLib->UnLoadLibrary();	
				XDELETE(pluginLib);				
			}
	}

	return bUnLoad;
}
