#ifndef TUTORIAL_MOUDLE2_H
#define TUTORIAL_MOUDLE2_H

#include "../../IGMainProject/IGInterface/IGIMoudle.h"
#include "../../IGMainProject/IGInterface/IGIPluginManager.h"

class TutorialMoudle2
	: public IGIMoudle
{
public:
	TutorialMoudle2();
	virtual ~TutorialMoudle2();

	virtual bool Awake();
	virtual bool Init();
	virtual bool AfterInit();
	virtual bool Update();
	virtual bool Finalize();
};

#endif //TUTORIAL_MOUDLE1_H

