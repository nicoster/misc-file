#include <windows.h>
#include <stdio.h>

void main()
{
    ULONG  HeapFragValue = 2;

    if(HeapSetInformation(GetProcessHeap(),
                       HeapCompatibilityInformation,
                       &HeapFragValue,
                       sizeof(HeapFragValue))
    )
    {
        printf("Success!\n");
    }
    else printf ("Failure (%d)\n", GetLastError());
}