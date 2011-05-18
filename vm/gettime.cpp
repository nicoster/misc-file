#include <windows.h>
#include <stdio.h>
void main()
{
wchar_t   wchDate[50];   
    
  SYSTEMTIME   t;   
  GetLocalTime(&t);   
    
  swprintf(wchDate,   L"%d-%d-%d %d:%d:%d",   t.wYear,t.wMonth,t.wDay, t.wHour, t.wMinute, t.wSecond);
	wprintf(wchDate);
}