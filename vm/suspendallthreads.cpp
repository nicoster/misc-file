#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <iostream.h>

extern "C"
WINBASEAPI
HANDLE
WINAPI
OpenThread(
    DWORD dwDesiredAccess,
    BOOL bInheritHandle,
    DWORD dwThreadId
    );
	
BOOL SuspendAllThreads () 
{ 
    HANDLE        hThreadSnap = NULL; 
    BOOL          bRet        = FALSE; 
    THREADENTRY32 te32        = {0}; 

    // Take a snapshot of all threads currently in the system. 

    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); 
    if (hThreadSnap == INVALID_HANDLE_VALUE) 
        return (FALSE); 

    // Fill in the size of the structure before using it. 

    te32.dwSize = sizeof(THREADENTRY32); 

    // Walk the thread snapshot to find all threads of the process. 
    // If the thread belongs to the process, add its information 
    // to the display list.

    DWORD dwOwnerPID = GetCurrentProcessId();
    if (Thread32First(hThreadSnap, &te32)) 
    { 
        do 
        { 
            if (te32.th32OwnerProcessID == dwOwnerPID && te32.th32ThreadID != GetCurrentThreadId()) 
            { 
                HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
                if (hThread != INVALID_HANDLE_VALUE)
                {
                    SuspendThread(hThread);
                    CloseHandle(hThread);
                }
            } 
        } 
        while (Thread32Next(hThreadSnap, &te32)); 
        bRet = TRUE; 
    } 
    else 
        bRet = FALSE;          // could not walk the list of threads 

    // Do not forget to clean up the snapshot object. 

    CloseHandle (hThreadSnap); 

    return (bRet); 
} 

void main()
{
    cout<<GetCurrentThreadId();
    SuspendAllThreads();
}
