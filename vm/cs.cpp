#include <windows.h>
#include <iostream.h>

void main()
{
	CRITICAL_SECTION cs;
	InitializeCriticalSection(&cs);
	EnterCriticalSection(&cs);
	cout << "a" << endl;
	EnterCriticalSection(&cs);
	cout << "b" << endl;
}