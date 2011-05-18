#define _AFXDLL
#include <afx.h>
#include <iostream.h>

void main()
{
	//~ _asm int 3;
	LPCTSTR p = "1";
	_asm push p;
	p = "2";
	_asm push p;
	
	CString cs;
	cs.FormatMessage("%1, %2, %3", "a");
	_asm add esp, 8;

	cout << cs << endl;
	
}