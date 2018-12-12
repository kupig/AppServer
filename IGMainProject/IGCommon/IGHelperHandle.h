#ifndef IG_HELPER_HANDLE
#define IG_HELPER_HANDLE

#include <stdio.h>
#include <string>

struct HelperHandle
{
	static bool GetFileContent(
		const std::string &filePath, std::string &content)
	{
		FILE *fp = fopen(filePath.c_str(), "rb");
		if (!fp) 
		{
			return false;
		}

		fseek(fp, 0, SEEK_END);
		const long size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		content.resize(size);
		fread((void *)content.data(), size, 1, fp);
		fclose(fp);

		return true;
	}
};

#endif //IG_HELPER_HANDLE
