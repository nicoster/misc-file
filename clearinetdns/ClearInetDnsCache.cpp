// ClearInetDnsCache.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <tchar.h>
#include <wininet.h>
#pragma comment( lib, "wininet.lib" )

// Now we have to define _NO_CVCONST_H to be able to access 
// various declarations from DbgHelp.h, which are not available by default 
#define _NO_CVCONST_H
#include "dbghelp.h"
#pragma comment( lib, "dbghelp.lib" )

#include <stdio.h>

bool GetFileParams( const TCHAR* pFileName, DWORD64& BaseAddr, DWORD& FileSize );
bool GetFileSize( const TCHAR* pFileName, DWORD& FileSize );
void OpenUrl(TCHAR* szUrl);

typedef void (__stdcall*  FlushResolverCacheProc)(void);
FlushResolverCacheProc FlushResolverCache = 0, FlushSystemResolverCache = 0;
typedef void (__stdcall* PurgeServerInfoListProc)(BOOL);
PurgeServerInfoListProc PurgeServerInfoList = 0;
//////////////////////////////////////////////////////////////////////////////
// Directives 
//
int main(int argc, char* argv[])
{
	HMODULE hModule = LoadLibrary(_T("dnsapi.dll"));
	if (! hModule)
	{
		_tprintf(_T("Error: LoadLibrary(dnsapi.dll) failed. Error code: %u \n"), ::GetLastError());
		return 0; 
	}

	FlushSystemResolverCache = (FlushResolverCacheProc)GetProcAddress(hModule, "DnsFlushResolverCache");
	if (! FlushSystemResolverCache)
	{
		_tprintf(_T("Error: GetProcAddress(DnsFlushResolverCache) failed. Error code: %u \n"), ::GetLastError());
		return 0; 
	}

	BOOL bRet = ::SymInitialize ( 
	            GetCurrentProcess(),  // Process handle of the current process 
	            NULL,                 // No user-defined search path -> use default 
	            FALSE                 // Do not load symbols for modules in the current process 
	          ); 
	
	if( !bRet ) 
	{
		_tprintf(_T("Error: SymInitialize() failed. Error code: %u \n"), ::GetLastError());
		return 0; 
	}

	do
	{
		hModule = LoadLibrary(_T("wininet.dll"));
		if (! hModule)
		{
			_tprintf(_T("Error: LoadLibrary(wininet.dll) failed. Error code: %u \n"), ::GetLastError());
			break; 
		}

		TCHAR buf[MAX_PATH];
		ZeroMemory(buf, MAX_PATH);
		GetModuleFileName(hModule, buf, MAX_PATH - 1);
		_tprintf(_T("%s\n"), buf);
		
		// Load symbols for the module 

		_tprintf( _T("Loading symbols for wininet ... \n")); 

		DWORD64 ModBase = ::SymLoadModule64 ( 
								GetCurrentProcess(), // Process handle of the current process 
								NULL,                // Handle to the module's image file (not needed)
								buf,           // Path/name of the file 
								NULL,                // User-defined short name of the module (it can be NULL) 
								0,            // Base address of the module (cannot be NULL if .PDB file is used, otherwise it can be NULL) 
								0             // Size of the file (cannot be NULL if .PDB file is used, otherwise it can be NULL) 
							); 

		if( ModBase == 0 ) 
		{
			_tprintf(_T("Error: SymLoadModule64() failed. Error code: %u \n"), ::GetLastError());
			break; 
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
			return 0;
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
			return 0;
		}
		else 
		{
			PurgeServerInfoList = (PurgeServerInfoListProc)(void*)sip.si.Address;
			_tprintf( _T("PurgeServerInfoList: %08x \n"), sip.si.Address ); 
		}
		
	} while (0);
	
	_tprintf(_T("Navigate www.baidu.com...\n===========================================\n"));
	OpenUrl(_T("http://www.baidu.com"));
	_tprintf(_T("\n\nNow you can modify your hosts file to redirect www.baidu.com to somewhere else. \nPress Enter to continue...\n\n"));
	getchar();
	_tprintf(_T("Navigate www.baidu.com again...\n===========================================\n"));
	FlushResolverCache();
	FlushSystemResolverCache();
	PurgeServerInfoList(TRUE);
	OpenUrl(_T("http://www.baidu.com/search/error.html"));

	return 0;
}

void OpenUrl(TCHAR* szUrl)
{
	HINTERNET hinet = InternetOpen(_T("ClearInetDnsCache"), INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
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
			printf( "%s \n", buf); 
	}

	InternetCloseHandle(hFile);
	InternetCloseHandle(hinet);

}
