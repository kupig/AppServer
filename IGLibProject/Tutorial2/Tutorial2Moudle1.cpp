#include "Tutorial2Moudle1.h"
#include "../../IGMainProject/IGCommon/IGPlatform.h"
#include "../../IGMainProject/IGPluginMoudle/IGITutorial1Moudle1.h"

Tutorial2Moudle1::Tutorial2Moudle1(IGIPluginManager *p)
{
	pPluginManager = p;
}

Tutorial2Moudle1::~Tutorial2Moudle1()
{
}

bool
Tutorial2Moudle1::Awake()
{
	PRINT_FUNC();
	return true;	
}

bool
Tutorial2Moudle1::Init()
{
	PRINT_FUNC();

	IGITutorial1Moudle1 *pTutorial1Moudle1 = ((IGIPluginManager *)pPluginManager)->FindMoudle<IGIMoudle, IGITutorial1Moudle1>();
	pTutorial1Moudle1->Test();

	return true;
}

bool
Tutorial2Moudle1::AfterInit()
{
	PRINT_FUNC();
	return true;
}

bool
Tutorial2Moudle1::Update()
{
	PRINT_FUNC();
	return true;
}

bool
Tutorial2Moudle1::Finalize()
{
	PRINT_FUNC();
	return true;
}

void 
Tutorial2Moudle1::Test()
{
	printf("===>>>>>>Tutorial2Moudle1, Test()\n");
}

