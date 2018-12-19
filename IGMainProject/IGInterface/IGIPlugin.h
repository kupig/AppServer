#ifndef IG_IPLUGIN_H
#define IG_IPLUGIN_H

#include "IGIMoudle.h"
#include "../IGCommon/IGMap.h"

#define CREATE_PLUGIN_OBJECT(pPluginManager, className)		\
	IGIPlugin* p##className = new className(pPluginManager);\
	pPluginManager->RegisterPlugin(p##className);

#define DESTROY_PLUGIN_OBJECT(pPluginManager, className)	\
	IGIPlugin *p##className = pPluginManager->FindPlugin(#className);\
	pPluginManager->UnregisterPlugin(p##className);

#define REGISTER_MOUDLE(pPluginManager, className)		\
	do {							\
		IGIMoudle *pMoudle##className = new className();\
		Add(#className, pMoudle##className);		\
	} while (0)

#define UNREGISTER_MOUDLE(pPluginManager, className)		\
	do {							\
		IGIMoudle *pMoudele##className = Remove(#className);\
		delete pMoudele##className;			\
	} while (0)

#define EXEC_EACH_MOUDLE(FUNC_NAME)				\
	IGIMoudle* pMoudle = First();				\
	while (pMoudle)	{					\
		pMoudle->FUNC_NAME();				\
		pMoudle = Next();				\
	}

class IGIPlugin
	: public IGIMoudle
	, public IGMap<std::string, IGIMoudle>
{
public:
	IGIPlugin() {}
	virtual ~IGIPlugin() {}

	virtual bool Awake() 
	{
		EXEC_EACH_MOUDLE(Awake);		
		return true; 
	}

	virtual bool Init()
   	{
		EXEC_EACH_MOUDLE(Init);	
		return true;
   	}

	virtual bool AfterInit() 
	{ 
		EXEC_EACH_MOUDLE(AfterInit);
		return true; 
	}

	virtual bool Update() 
	{ 
		EXEC_EACH_MOUDLE(Update);
		return true; 
	}

	virtual bool Finalize()
   	{ 
		EXEC_EACH_MOUDLE(Finalize);
		return true; 
	}

	virtual void InstallMoudle() = 0;
	virtual void UninstallMoudle() = 0;
	virtual std::string GetPluginName() = 0; 
};

#endif // IG_IPLUGIN_H
