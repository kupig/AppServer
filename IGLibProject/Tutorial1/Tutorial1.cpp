#include "Tutorial1.h"
#include <stdio.h>

extern "C" void LibPluginStart()
{
	printf("hello, this is tutorial.so start.\n");
}

extern "C" void LibPluginStop()
{
	printf("hello, this is tutorial.so end.\n");
}
