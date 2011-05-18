#define _WIN32_WINNT		0x0500

#ifndef _WIN32_IE
#define	_WIN32_IE			0x0500
#endif

#include <windows.h>
#include <iostream.h>

DWORD WINAPI Proc(LPVOID)
{
	HANDLE h = CreateEvent(0, 0, 0, "NICK_EVENT");
	Sleep(1000);
//	SetEvent(h);
	CloseHandle(h);
	return 0;
}

void main()
{
	MessageBox(0, 0, 0, 0);
	//~ QueueUserWorkItem(Proc, 0, 0);
	HANDLE h = CreateEvent(0, 0, TRUE, "NICK_EVENT");
	_asm int 3;
	DWORD dw = WaitForSingleObject(h, INFINITE);
	_asm int 3;
	dw = WaitForSingleObject(h, 0);
	_asm int 3;
	CloseHandle(h);
	_asm int 3;
}