// win2000 SDK or above
// cl.exe -MT userapc.cpp 

#define _WIN32_WINNT 0x0500
#include "windows.h"
#include "process.h"

void WINAPI procwait(LPVOID, BYTE)
{
}

UINT WINAPI proc_thrd(LPVOID)
{
	OutputDebugString("in thread before sleepex. \n");
	SleepEx(10000, TRUE);
	OutputDebugString("in thread after sleepex. \n");
	return 0;
}

VOID CALLBACK APCProc(ULONG_PTR dwParam)
{
	OutputDebugString("in APCProc \n");
	
}

DWORD main(void)
{
	OutputDebugString("start.... \n");
	HANDLE hWorkThread;
	UINT nThreadID;
	hWorkThread = (HANDLE)_beginthreadex(NULL,					// Security
		0,						// Stack size - use default
		proc_thrd,     		// Thread fn entry point
		(void*) 0,			// Param for thread
		0,						// Init flag
		&nThreadID);			// Thread address
	Sleep(100);
	DWORD dwRet = QueueUserAPC(APCProc, hWorkThread, 0);
	WaitForSingleObject(hWorkThread, INFINITE);
	
	HANDLE hWait = NULL;
	RegisterWaitForSingleObject(&hWait, INVALID_HANDLE_VALUE, procwait, NULL, INFINITE, 0);
	return dwRet;
}