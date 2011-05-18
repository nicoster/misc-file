#include <windows.h>
#include <wininet.h>
#include <iostream.h>
#pragma comment(lib, "wininet.lib")

void main()
{
	HINTERNET hinet = InternetOpen("dummy", INTERNET_OPEN_TYPE_PROXY, "172.31.0.3:8080", 0, INTERNET_FLAG_ASYNC);
	char buf[MAX_PATH + 1];
	DWORD len = MAX_PATH;
	BOOL bRet;
	if (bRet = InternetQueryOption(hinet, INTERNET_OPTION_PROXY_USERNAME, buf, &len))
	{
		buf[len] = 0;
		cout << buf << ":";
	}

	len = MAX_PATH;
	if (bRet && (bRet = InternetQueryOption(hinet, INTERNET_OPTION_PROXY_PASSWORD, buf, &len)))
	{
		buf[len] = 0;
		cout << buf << endl;
	}
	
}