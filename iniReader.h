#pragma once

#include <string>
#include <Windows.h>

class IniReader {
public:
	IniReader(char *iniPath) : iniPath(iniPath) {}

	inline bool fileExists() {return GetFileAttributes(iniPath) != INVALID_FILE_ATTRIBUTES;}

	bool readBool(std::string section, std::string key, bool defaultVal, bool &result);
	bool readInt(std::string section, std::string key, int defaultVal, int base, int &result);
	bool readFloat(std::string section, std::string key, float defaultVal, float &result);
	bool readString(std::string section, std::string key, std::string defaultVal, std::string &result);

private:
	char *iniPath;
};