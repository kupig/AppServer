#include "IGDynamicLib.h"
#include <dlfcn.h>
#include <stdio.h>

IGDynamicLib::IGDynamicLib(const std::string& pluginName)
	: mPluginName(pluginName)
{
}

IGDynamicLib::~IGDynamicLib()
{
}

bool
IGDynamicLib::LoadLibrary()
{
	std::string libPath = "./" + mPluginName + ".so";
	mLibHandle = dlopen(libPath.c_str(), RTLD_LAZY);
	if (!mLibHandle)
	{
		printf("load %s error, %.s\n", libPath.c_str(), dlerror());
	}
	return mLibHandle != NULL;
}

bool
IGDynamicLib::UnLoadLibrary()
{
	if (!mLibHandle)
	{
		printf("Failed to unload %s.\n", mPluginName.c_str());
		return false;
	}

	dlclose(mLibHandle);
	return true;
}

void *
IGDynamicLib::GetSymbol(const std::string &symName)
{
	if (!mLibHandle)
	{
		printf("Failed to unload %s.\n", mPluginName.c_str());
	}
	return dlsym(mLibHandle, symName.c_str());
}
