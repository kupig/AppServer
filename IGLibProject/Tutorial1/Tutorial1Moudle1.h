#ifndef TUTORIAL_MOUDLE1_H
#define TUTORIAL_MOUDLE1_H

#include "../../IGMainProject/IGPluginMoudle/IGITutorial1Moudle1.h"
#include "../../IGMainProject/IGInterface/IGIPluginManager.h"


class Tutorial1Moudle1
	: public IGITutorial1Moudle1
{
public:
	Tutorial1Moudle1(IGIPluginManager *p);
	virtual ~Tutorial1Moudle1();

	virtual bool Awake();
	virtual bool Init();
	virtual bool AfterInit();
	virtual bool Update();
	virtual bool Finalize();

	void Test();
};

#endif //TUTORIAL_MOUDLE1_H

