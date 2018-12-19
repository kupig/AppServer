#ifndef IG_DYNAMIC_LIB_H
#define IG_DYNAMIC_LIB_H

#include <string>

class IGDynamicLib
{
public:
	IGDynamicLib(const std::string& pluginName);
	~IGDynamicLib();

	bool LoadLibrary();
	bool UnLoadLibrary();
	void* GetSymbol(const std::string &symName);
		
private:
	std::string mPluginName;
	void *mLibHandle;


};

#endif // IG_DYNAMIC_LIB_H
