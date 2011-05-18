#define UNICODE
#define _UNICODE
#include "common.h"

bool IsIEDefault()
{
	CRegKey key;
	if (ERROR_SUCCESS != key.Open(HKEY_CLASSES_ROOT, L"http\\shell\\open\\command", KEY_READ))
		return true;
	
	TCHAR szValue[1024];
	DWORD nCount = 1024;
	ZeroMemory(szValue, 1024 * sizeof TCHAR);
	if (ERROR_SUCCESS != key.QueryValue(szValue, L"", &nCount))
		return true;

	wcout << szValue << endl;
	wstring strValue(szValue);
//	strValue.MakeLower();
	return -1 != strValue.find(L"iexplore.exe");
}

void main()
{
	bool b = IsIEDefault();
}