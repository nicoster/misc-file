#include <windows.h>
#include <wininet.h>
#include <atlbase.h>
#include <iostream>
using namespace std;

#pragma comment(lib, "wininet.lib")
#define exit {cout << GetLastError() << endl; return GetLastError();}

BOOL flushDnsCache();

int main()
{
	cout << "Press Enter to continue" << endl;
	while (getchar())
	{		
		cout << "Issuing a request...\n\n";
		HINTERNET hInet = InternetOpen("testflushdns", INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
		if (! hInet) exit;
		
		HINTERNET hFile = InternetOpenUrl(hInet, "http://shawapi.webexconnect.com/wbxconnect/op.do", "Connection: close", -1, 0, 0);
		if (!hFile) exit;
			
		char buf[1024]; DWORD bytesread = 0;
		InternetReadFile(hFile, buf, 1023, &bytesread);
		buf[min(1023, bytesread)] = 0;
		cout << buf << endl;

		InternetCloseHandle(hFile);
		InternetCloseHandle(hInet);
		
		// flush dns
		CRegKey key;
		if (ERROR_SUCCESS != key.Open(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\DNSCache\\Parameters", KEY_WRITE))	exit;
		LONG ret = key.SetValue((DWORD)0, "MaxCacheEntryTtlLimit");
		if (ret != ERROR_SUCCESS) exit;
			
		flushDnsCache();
	}
	
	return 0;
}

BOOL flushDnsCache()
{
	HMODULE hDNSApi = LoadLibrary("dnsapi.dll");    
	if(NULL != hDNSApi)
	{
		typedef BOOL   (WINAPI   *RADNSFLUSHPROC)(VOID);    
		RADNSFLUSHPROC pDnsFlushProc = NULL;        
		if(NULL != (pDnsFlushProc = (RADNSFLUSHPROC)GetProcAddress(hDNSApi, "DnsFlushResolverCache")))
		{
			if (!pDnsFlushProc())     
				return FALSE;
		}
		else
			return FALSE;
		
		pDnsFlushProc = NULL;
		FreeLibrary(hDNSApi);
		return TRUE;        
	}
	return FALSE;
}