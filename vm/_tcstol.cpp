#include <stdlib.h>
#include <tchar.h>
#include <iostream.h>

void main()
{
	int i =  _tcstol(_T("12"), 0, 10);
	cout<<i;
}