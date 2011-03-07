// ClearInetDnsCache.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <tchar.h>
#include <wininet.h>
#pragma comment( lib, "wininet.lib" )

#define _NO_CVCONST_H
#include "dbghelp.h"
#pragma comment( lib, "dbghelp.lib" )

#include <TLHELP32.H>

#include <stdio.h>

void OpenUrl(TCHAR* szUrl);
BOOL InitFuncPtrs(void);

typedef void (__stdcall*  FlushResolverCacheProc)(void);
FlushResolverCacheProc FlushResolverCache = 0, FlushSystemResolverCache = 0;
typedef void (__stdcall* PurgeServerInfoListProc)(BOOL);
PurgeServerInfoListProc PurgeServerInfoList = 0;
PLIST_ENTRY GlobalServerInfoList = 0;
BOOL ShowServerInfoList();

int main(int argc, char* argv[])
{
	if (!InitFuncPtrs()) return 1;
	
	_tprintf(_T("Navigate www.baidu.com...\n===========================================\n"));
	OpenUrl(_T("https://hzswapi.qa.webex.com/wbxconnect/op.do"));
//	OpenUrl(_T("http://www.kaixin001.com"));
	
	ShowServerInfoList();

	_tprintf(_T("\n\nNow you can modify hosts file to redirect www.baidu.com to somewhere else. \nPress Enter to continue...\n\n"));
	getchar();
	
	PurgeServerInfoList(TRUE);
	FlushResolverCache();
	FlushSystemResolverCache();
	
	_tprintf(_T("Navigate www.baidu.com again...\n===========================================\n"));
	OpenUrl(_T("http://www.baidu.com"));

	return 0;
}

BOOL ShowServerInfoList()
{
	if(! GlobalServerInfoList) return FALSE;
	try
	{
		for (PLIST_ENTRY cur = GlobalServerInfoList->Flink; cur != GlobalServerInfoList && cur != 0; cur = cur->Flink)
		{
			char* name = *(char**)((char*)cur + 0x14);
			int refcount = *(int*)((char*)cur + 0x10);
			_tprintf( _T("%08x, %s, %d \n"),  cur, name, refcount); 
		}
	}
	catch(...)
	{
		printf("error when walkthrough server info list");
		return FALSE;
	}

	return TRUE;
}

void OpenUrl(TCHAR* szUrl)
{
	char* proxies = "1.1.1.1:2345 10.224.104.179:9090 10.224.170.11:8080";
//	char* proxies = "ftp=http://10.224.104.179:2345 http=http://10.224.104.179:9090 gopher=http://10.224.170.11:8080";
//	char* proxies = L"10.224.104.179:9090";

//	HINTERNET hinet = InternetOpen(_T("ClearInetDnsCache"), INTERNET_OPEN_TYPE_PROXY, proxies, 0, 0);
	HINTERNET hinet = InternetOpen(_T("ClearInetDnsCache"), INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
	if (!hinet)
	{
			_tprintf( _T("Error: InternetOpen() failed. Error code: %u \n"), ::GetLastError() ); 
	}

	HINTERNET hFile = InternetOpenUrl(hinet, szUrl, 0, 0, INTERNET_FLAG_RELOAD, 0);
	if (!hFile)
	{
			_tprintf( _T("Error: InternetOpenUrl() failed. Error code: %u \n"), ::GetLastError() ); 
	}

#define BUFLEN 1024
	char buf[BUFLEN];
	ZeroMemory(buf, BUFLEN);
	DWORD len = 0;
	BOOL bRet = InternetReadFile(hFile, buf, BUFLEN - 1, &len);
	if (bRet)
	{
			_tprintf( "%s \n", buf); 
	}

	InternetCloseHandle(hFile);
	InternetCloseHandle(hinet);

}

BOOL InitFuncPtrs(void)
{
	HMODULE hModule = LoadLibrary(_T("dnsapi.dll"));
	if (! hModule)
	{
		_tprintf(_T("Error: LoadLibrary(dnsapi.dll) failed. Error code: %u \n"), ::GetLastError());
		return FALSE; 
	}

	FlushSystemResolverCache = (FlushResolverCacheProc)GetProcAddress(hModule, "DnsFlushResolverCache");
	if (! FlushSystemResolverCache)
	{
		_tprintf(_T("Error: GetProcAddress(DnsFlushResolverCache) failed. Error code: %u \n"), ::GetLastError());
		return FALSE; 
	}

	MODULEENTRY32	me32        = {0};
	bool found = false;
	HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if (hModuleSnap == INVALID_HANDLE_VALUE) 
	{
		return FALSE;
	}

	me32.dwSize = sizeof(MODULEENTRY32);

	BOOL bRet = Module32First(hModuleSnap, &me32);
	while (bRet) 
	{
		if (_tcsicmp(_T("wininet.dll"), me32.szModule) == 0) 
		{
			found = true;
			break;
		}

		ZeroMemory(&me32, sizeof(MODULEENTRY32));
		me32.dwSize = sizeof(MODULEENTRY32);
		
		bRet = Module32Next(hModuleSnap, &me32);
	}
	CloseHandle (hModuleSnap);

	if (! found)
	{
		_tprintf(_T("Error: wininet.dll not found! \n"));
		return FALSE;
	}


	bRet = ::SymInitialize ( 
	            GetCurrentProcess(),  // Process handle of the current process 
	            _T("SRV*c:\\*http://msdl.microsoft.com/download/symbols"),                 // No user-defined search path -> use default 
	            FALSE                 // Do not load symbols for modules in the current process 
	          ); 
	
	if( !bRet ) 
	{
		_tprintf(_T("Error: SymInitialize() failed. Error code: %u \n"), ::GetLastError());
		return FALSE; 
	}

	// Load symbols for the module 

	_tprintf( _T("Loading symbols for wininet ... \n")); 

	DWORD64 ModBase = ::SymLoadModule64 ( 
							GetCurrentProcess(), // Process handle of the current process 
							NULL,                // Handle to the module's image file (not needed)
							me32.szExePath,           // Path/name of the file 
							NULL,                // User-defined short name of the module (it can be NULL) 
							(DWORD)me32.modBaseAddr,            // Base address of the module (cannot be NULL if .PDB file is used, otherwise it can be NULL) 
							0             // Size of the file (cannot be NULL if .PDB file is used, otherwise it can be NULL) 
						); 

	if( ModBase == 0 ) 
	{
		_tprintf(_T("Error: SymLoadModule64() failed. Error code: %u \n"), ::GetLastError());
		return FALSE;
	}

	_tprintf( _T("Load address: %I64x \n"), ModBase ); 


	// Look up symbol by name 

	_tprintf( _T("Looking for symbol FlushResolverCache ... \n")); 

	SYMBOL_INFO_PACKAGE sip; 
	sip.si.SizeOfStruct = sizeof(SYMBOL_INFO); 
	sip.si.MaxNameLen   = sizeof(sip.name); 

	bRet = ::SymFromName( 
							GetCurrentProcess(), // Process handle of the current process 
							_T("FlushResolverCache"),            // Symbol name 
							&sip.si              // Address of the SYMBOL_INFO structure (inside "sip" object) 
						);

	if( !bRet ) 
	{
		_tprintf( _T("Error: SymFromName() failed. Error code: %u \n"), ::GetLastError() ); 
		if (::GetLastError() == 126)
		{
			_tprintf( _T("The error may occur if symsrv.dll/dbghelp.dll are absent. \n")); 
		}
		return FALSE;
	}
	else 
	{
		FlushResolverCache = (FlushResolverCacheProc)(void*)sip.si.Address;
		_tprintf( _T("FlushResolverCache: %08x \n"), sip.si.Address ); 
	}

	bRet = ::SymFromName( 
							GetCurrentProcess(), // Process handle of the current process 
							_T("PurgeServerInfoList"),            // Symbol name 
							&sip.si              // Address of the SYMBOL_INFO structure (inside "sip" object) 
						);

	if( !bRet ) 
	{
		_tprintf( _T("Error: SymFromName() failed. Error code: %u \n"), ::GetLastError() ); 
		if (::GetLastError() == 126)
		{
			_tprintf( _T("The error may occur if symsrv.dll/dbghelp.dll are absent. \n")); 
		}
		return FALSE;
	}
	else 
	{
		PurgeServerInfoList = (PurgeServerInfoListProc)(void*)sip.si.Address;
		_tprintf( _T("PurgeServerInfoList: %08x \n"), sip.si.Address ); 
	}

	bRet = ::SymFromName( 
							GetCurrentProcess(), // Process handle of the current process 
							_T("GlobalServerInfoList"),            // Symbol name 
							&sip.si              // Address of the SYMBOL_INFO structure (inside "sip" object) 
						);

	if( !bRet ) 
	{
		_tprintf( _T("Error: SymFromName() failed. Error code: %u \n"), ::GetLastError() ); 
		if (::GetLastError() == 126)
		{
			_tprintf( _T("The error may occur if symsrv.dll/dbghelp.dll are absent. \n")); 
		}
		return FALSE;
	}
	else 
	{
		GlobalServerInfoList = (PLIST_ENTRY)(void*)sip.si.Address;
		_tprintf( _T("GlobalServerInfoList: %08x \n"), sip.si.Address ); 
	}
	
	return TRUE;
}