#include "Tutorial1Moudle1.h"
#include "../../IGMainProject/IGCommon/IGPlatform.h"

Tutorial1Moudle1::Tutorial1Moudle1(IGIPluginManager *p)
{
	pPluginManager = p;
}

Tutorial1Moudle1::~Tutorial1Moudle1()
{
}

bool
Tutorial1Moudle1::Awake()
{
	PRINT_FUNC();
	return true;	
}

bool
Tutorial1Moudle1::Init()
{
	PRINT_FUNC();
	return true;
}

bool
Tutorial1Moudle1::AfterInit()
{
	PRINT_FUNC();
	return true;
}

bool
Tutorial1Moudle1::Update()
{
	PRINT_FUNC();
	return true;
}

bool
Tutorial1Moudle1::Finalize()
{
	PRINT_FUNC();
	return true;
}

void 
Tutorial1Moudle1::Test()
{
	printf("===>>>>>>Tutorial1Moudle1, Test()\n");
}

