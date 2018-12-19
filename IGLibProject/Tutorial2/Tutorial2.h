#ifndef TUTORIAL2_H
#define TUTORIAL2_H

#include "../../IGMainProject/IGInterface/IGIPlugin.h"
#include "../../IGMainProject/IGInterface/IGIPluginManager.h"

class Tutorial2: public IGIPlugin
{
public:
	Tutorial2(IGIPluginManager *p);
	virtual ~Tutorial2();

	virtual void InstallMoudle();
	virtual void UninstallMoudle();

	std::string GetPluginName();
};

#endif //TUTORIAL2_H
