#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream.h>

VOID CALLBACK DummyAPCProc(DWORD){}
VOID CALLBACK TimerRoutine(PVOID lpParam, BYTE /*TimerOrWaitFired*/)
{
	HANDLE h = (HANDLE)lpParam;
	QueueUserAPC(DummyAPCProc, h, NULL);
	CloseHandle(h);
}


void main()
{
	HANDLE hAlertThread;
	DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), 
		GetCurrentProcess(), &hAlertThread, 
		0, FALSE, DUPLICATE_SAME_ACCESS);
	
	HANDLE hTimer;
	if (! CreateTimerQueueTimer(&hTimer, NULL, TimerRoutine, hAlertThread, 100, 0, WT_EXECUTEONLYONCE))
		
	Sleep(200);
	cout<<"start sleepex\n";
	if (0 == SleepEx(200, TRUE))
		cout<<"sleepex timeout.\n";
	else
		cout<<"sleepex alerted\n";
	
}