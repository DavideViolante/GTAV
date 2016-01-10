#include "iniReader.h"
#include <stdexcept>

bool IniReader::readBool(std::string section, std::string key, bool defaultVal, bool &result) {
	char buf[32];
	DWORD num = GetPrivateProfileString(section.c_str(), key.c_str(), "", buf, 32, iniPath);
	std::string value = std::string(buf);
	if(value == "true") {
		result = true;
	} else if(value == "false") {
		result = false;
	} else {
		return false;
	}
	return true;
}

bool IniReader::readInt(std::string section, std::string key, int defaultVal, int base, int &result) {
	char buf[32];
	DWORD num = GetPrivateProfileString(section.c_str(), key.c_str(), "", buf, 32, iniPath);
	try {
		std::size_t numRead = 0;
		result = std::stoi(buf, &numRead, base);
		if(numRead != num) {
			result = defaultVal;
			return false;
		}
		return true;
	} catch(std::exception&) {
		result = defaultVal;
		return false;
	}
}

bool IniReader::readFloat(std::string section, std::string key, float defaultVal, float &result) {
	char buf[32];
	DWORD num = GetPrivateProfileString(section.c_str(), key.c_str(), "", buf, 32, iniPath);
	try {
		std::size_t numRead = 0;
		result = std::stof(buf, &numRead);
		if(numRead != num) {
			result = defaultVal;
			return false;
		}
		return true;
	} catch(std::exception&) {
		result = defaultVal;
		return false;
	}
}

bool IniReader::readString(std::string section, std::string key, std::string defaultVal, std::string &result) {
	char buf[256];
	DWORD num = GetPrivateProfileString(section.c_str(), key.c_str(), defaultVal.c_str(), buf, 256, iniPath);
	result = std::string(buf);
	return true;
}