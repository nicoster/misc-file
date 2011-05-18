#define _UNICODE
#define UNICODE
#include "common.h"

typedef wstring CTString;

CTString GetCertFolder()
{
	CTString strPath;
	TCHAR szPath[MAX_PATH];
	GetSystemDirectory(szPath, MAX_PATH);
	strPath = szPath;
	strPath += L"\\shell32.dll";
//	wcout << strPath;
//DEL 	PathAppend(szPath, _T("shell32.dll"));

	HMODULE hModule = LoadLibrary(strPath.c_str());
	if(!hModule)		return L"";

	typedef BOOL (WINAPI *SHGetSpecialFolderPathPtr)(HWND, LPTSTR, int, BOOL);
	SHGetSpecialFolderPathPtr _SHGetSpecialFolderPath = (SHGetSpecialFolderPathPtr)GetProcAddress(hModule, "SHGetSpecialFolderPathW");
	if(_SHGetSpecialFolderPath && _SHGetSpecialFolderPath(0, szPath, 0x001a/*CSIDL_APPDATA*/, TRUE))
	{
		strPath = szPath;
		strPath += L"\\WebEx Connect\\cert\\";
	}
	FreeLibrary(hModule);
	return strPath;

//DEL 	TCHAR szBuffer[1024] = {0};
//DEL 	DWORD dwLen = ::GetModuleFileName(GetModuleHandle(0), szBuffer, 1023);
//DEL 
//DEL 	if(dwLen <= 0)
//DEL 	{
//DEL 		return L"";
//DEL 	}
//DEL 
//DEL 	while(dwLen > 0 && szBuffer[dwLen-1] != _T('\\'))
//DEL 	{
//DEL 		dwLen--;
//DEL 	}
//DEL 	szBuffer[dwLen] = _T('\0');
//DEL 	return CTString(szBuffer) + L"cert\\";
}


void main()
{
//	int3;
	wcout << GetCertFolder().c_str();
}