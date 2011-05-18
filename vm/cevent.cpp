#include <afxmt.h>
#include <iostream>

#pragma comment(linker, "/defaultlib:msvcrt.lib")

void main()
{
	CEvent evt;
	evt.SetEvent();
	//~ HANDLE evt = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (WAIT_TIMEOUT == WaitForSingleObject(evt, 1000))
		std::cout<<"Timeout\n";
	else
		std::cout<<"succeed\n";
}