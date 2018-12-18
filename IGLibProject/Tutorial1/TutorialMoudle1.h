#ifndef TUTORIAL_MOUDLE1_H
#define TUTORIAL_MOUDLE1_H

#include "../../IGMainProject/IGInterface/IGIMoudle.h"
#include "../../IGMainProject/IGInterface/IGIPluginManager.h"

class TutorialMoudle1
	: public IGIMoudle
{
public:
	TutorialMoudle1();
	virtual ~TutorialMoudle1();

	virtual bool Awake();
	virtual bool Init();
	virtual bool AfterInit();
	virtual bool Update();
	virtual bool Finalize();
};

#endif //TUTORIAL_MOUDLE1_H

