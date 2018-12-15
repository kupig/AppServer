#ifndef IG_PLATFORM_H
#define IG_PLATFORM_H


#define IG_PLATFORM_WINDOWS 1
#define IG_PLATFORM_LINUX	2
#define IG_PLATFORM_MACOS	3
#define IG_PLATFORM_ANDROID	4

#ifdef _WIN32
	#ifdef _WIN64
	#	define IG_PLATFORM IG_PLATFORM_WINDOWS	
	#else
	#	define IG_PLATFORM IG_PLATFORM_WINDOWS
	#endif
#elif __APPLE__
	#include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
	#   define IG_PLATFORM IG_PLATFORM_MACOS
    #elif TARGET_OS_IPHONE
	#   define IG_PLATFORM IG_PLATFORM_MACOS    
    #elif TARGET_OS_MAC
	#   define IG_PLATFORM IG_PLATFORM_MACOS
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __ANDROID__
    // android
#elif __linux__
#   define IG_PLATFORM IG_PLATFORM_LINUX
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif


#if IG_PLATFORM == IG_PLATFORM_LINUX
#include <sys/prctl.h>
#endif

#define PRINT_FUNC() 		\
	(printf("IGPluginManager::%s()\n", __FUNCTION__))

#define XDELETE(POINT) do 	\
	{						\
		delete POINT; 		\
		POINT = NULL;		\
	} while (0)

#endif // IG_PLATFORM_H
