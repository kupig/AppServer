#ifndef TUTORIAL_MOUDLE1_H
#define TUTORIAL_MOUDLE1_H

#include "../../IGMainProject/IGPluginMoudle/IGITutorial2Moudle1.h"
#include "../../IGMainProject/IGInterface/IGIPluginManager.h"

class Tutorial2Moudle1
	: public IGIMoudle
{
public:
	Tutorial2Moudle1(IGIPluginManager *p);
	virtual ~Tutorial2Moudle1();

	virtual bool Awake();
	virtual bool Init();
	virtual bool AfterInit();
	virtual bool Update();
	virtual bool Finalize();

	void Test();
};

#endif //TUTORIAL_MOUDLE1_H

