#include <windows.h>
#include <iostream.h>

void main()
{
	SetLastError(1234);
	try{*(int*)0=0;}
	catch(...){SetLastError(2345);}
	DWORD dw = GetLastError();
	cout << dw;
}