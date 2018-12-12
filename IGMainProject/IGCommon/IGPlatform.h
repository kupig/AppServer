#ifndef IG_PLATFORM_H
#define IG_PLATFORM_H

#include <sys/prctl.h>

#define PRINT_FUNC() 		\
	(printf("IGPluginManager::%s()\n", __FUNCTION__))

#define XDELETE(POINT) do 	\
	{						\
		delete POINT; 		\
		POINT = NULL;		\
	} while (0)

#endif // IG_PLATFORM_H
