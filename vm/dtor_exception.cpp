
#include <windows.h>
#include <iostream.h>

LONG __stdcall _UnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{	
	return EXCEPTION_EXECUTE_HANDLER;
}

void foo()
{
	struct bar{~bar(){cout << "dtor\n";}} zoo;
//	 *(int*)0 = 0;
	throw 0;
}

void main()
{
	SetUnhandledExceptionFilter(_UnhandledExceptionFilter);

	//~ try{
	foo();
	//~ }
	//~ catch(...){}
}