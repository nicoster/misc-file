#include <windows.h>

LONG __stdcall _UnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	MessageBox(0, "aaa", "aaa", 0);
	_asm int 3;
	return 0;
}

void main()
{
//	SetUnhandledExceptionFilter(_UnhandledExceptionFilter);
	memset(0, 1, 1);
}