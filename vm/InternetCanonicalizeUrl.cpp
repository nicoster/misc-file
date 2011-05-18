#include <windows.h>
#include <wininet.h>
#include <tchar.h>
#include <iostream.h>
#pragma comment(lib, "wininet.lib")
void main()
{
	_asm int 3;
	TCHAR buf0[] = {0x25, 0x34, 0xe4, 0xbd, 0xa0, 0};
	TCHAR buf[256];
	DWORD len = 256;
	DWORD dw = InternetCanonicalizeUrl(buf0/*_T("%Äã")*/, buf, &len, 0x1000);
	cout<< dw<<endl;
	dw = GetLastError();
	cout << buf <<endl;
	cout << len <<endl;
}