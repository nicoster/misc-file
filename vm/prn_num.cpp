#include "common.h"

HANDLE h1 = 0, h2 = 0;
CRITICAL_SECTION cs;
HANDLE event, mutex;
long n = 0;

void lock_cs()
{
	EnterCriticalSection(&cs);
}

void unlock_cs()
{
	LeaveCriticalSection(&cs);
}

void lock_event()
{
	WaitForSingleObject(event, INFINITE);
}

void unlock_event()
{
	SetEvent(event);
}

void lock_mutex()
{
	WaitForSingleObject(mutex, INFINITE);
}

void unlock_mutex()
{
	ReleaseMutex(mutex);
}

DWORD WINAPI proc(void* p)
{
	int const& index = (int)p;
	while (1)
	{
		lock_mutex();
		
		cout << index << ":" << n << endl;
		int m = InterlockedIncrement(&n);
		
		if (m / index * index != m) exit(1);
		
		unlock_mutex();
	}
	return 0;
}

void main()
{
	InitializeCriticalSection(&cs);
	event = CreateEvent(0, 0, 1, 0);
	mutex = CreateMutex(0, 0, 0);
	
	h1 = CreateThread(0, 0, proc, (void*) 1, 0, 0);
	h2 = CreateThread(0, 0, proc, (void*) 2, 0, 0);
	WaitForMultipleObjects(2, &h1, 1, INFINITE); 
}