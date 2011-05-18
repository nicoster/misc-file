#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdio.h>

DWORD g_dwLastTick;

void CALLBACK Tick(void *, BOOLEAN)
{
    DWORD dwTick = GetTickCount();
    printf("%5d\n", dwTick - g_dwLastTick);
}

DWORD CALLBACK Clog(void *)
{
    Sleep(4000);
    return 0;
}

int __cdecl
main(int argc, char* argv[])
{
    g_dwLastTick = GetTickCount();
    switch (argc)
    {
    case 2:
        QueueUserWorkItem(Clog, NULL, 0);
        Sleep(INFINITE);
        break;
    case 3:
        QueueUserWorkItem(Clog, NULL, WT_EXECUTELONGFUNCTION);
        break;
    }
    HANDLE hTimer;
    CreateTimerQueueTimer(&hTimer, NULL, Tick, NULL, 250, 250, 0);
    Sleep(INFINITE);
    return 0;
}