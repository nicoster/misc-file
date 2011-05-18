#include <windows.h>
#include <iostream>
using namespace std;

void main(void)
{
	*(int*)0 = 0;
	HANDLE h = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (h == INVALID_HANDLE_VALUE)
	{
		cout<<"invalid handle";
		return;
	}
	
	DWORD dwRet = WaitForSingleObject(h, 0);
	cout <<"dwRet "<<dwRet;
}