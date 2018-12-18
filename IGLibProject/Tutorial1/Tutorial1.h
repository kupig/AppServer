#ifndef TUTORIAL1_H
#define TUTORIAL1_H

#include "../../IGMainProject/IGInterface/IGIPlugin.h"
#include "../../IGMainProject/IGInterface/IGIPluginManager.h"

class Tutorial1: public IGIPlugin
{
public:
	Tutorial1(IGIPluginManager *p);
	virtual ~Tutorial1();

	virtual void InstallMoudle();
	virtual void UninstallMoudle();

	std::string GetPluginName();
};

#endif //TUTORIAL1_H
