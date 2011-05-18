#include "Windows.h"
#include "tchar.h"
#include "stdlib.h"
#include "math.h" 

const double SPLIT = 0.01;
const int COUNT = 200;
const double PI = 3.14159265;
const int INTERVAL = 300; 

int _tmain(int argc, _TCHAR* argv[])
{
   SetProcessAffinityMask(
        GetCurrentProcess(),
        0x00000001          //cpu mask
        ); 

    DWORD busySpan[COUNT];  //array of busy times
    DWORD idleSpan[COUNT];  //array of idle times
    int half = INTERVAL / 2;
    double radian = 0.0;
    for(int i = 0; i < COUNT; i++)
    {
        busySpan[i] = (DWORD)(half + (sin(PI * radian) * half));
        idleSpan[i] = INTERVAL - busySpan[i];
        radian += SPLIT;
    }
    DWORD startTime = 0;
    int j = 0;
    while (true)
    {
        j = j % COUNT;
        startTime = GetTickCount();
        while ((GetTickCount() - startTime) <= busySpan[j]) ;
        Sleep(idleSpan[j]);
        j++;
    }
    return 0;
}