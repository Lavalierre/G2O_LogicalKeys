#include "registry.h"
#include <Windows.h>

bool readSZ(HKEY root, std::string subKey, std::string valueName, std::string& result)
{
	HKEY hKey;

	if (RegOpenKeyExA(root, subKey.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS)
		return false;

	DWORD type;
	DWORD size;

	if (RegQueryValueExA(hKey, valueName.c_str(), NULL, &type, NULL, &size) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return false;
	}

	if (type != REG_SZ)
		return false;

	result.resize(size);

	if (RegQueryValueExA(hKey, valueName.c_str(), NULL, &type, reinterpret_cast<LPBYTE>(&result[0]), &size) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return false;
	}

	result.resize(--size);
	RegCloseKey(hKey);

	return true;
}

std::string getIPPort()
{
	std::string result;
	readSZ(HKEY_CURRENT_USER, "Software\\G2O", "ip_port", result);

	return result;
}
