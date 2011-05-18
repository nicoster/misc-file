#include <afxcview.h>
#include <iostream.h>
#include "listctrlsort\listctrlsort.h"

void main()
{
	DWORD dw = GetTickCount();
	for (int i = 0; i < 1000000; i ++)
		ListCtrlSortHelper<CWnd>::Compare(_T("COM123COM456"), _T("COM123COM356"));
	cout<<GetTickCount() - dw<<endl;
}