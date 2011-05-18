#define UNICODE
#define _UNICODE
#include "common.h"
#include <atlbase.h>

void main()
{
	CRegKey reg;
	if (reg.Open(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings") == ERROR_SUCCESS)
	{
		//~ reg.SetValue(1, L"DnsCacheTimeout");
		//~ reg.SetValue(100, L"ServerInfoTimeOut");
		
		reg.DeleteValue(L"DnsCacheTimeout");
		reg.DeleteValue(L"ServerInfoTimeOut");
	}
	
}