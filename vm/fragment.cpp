#include "afx.h"

void main()
{
	while (1)
	{
		Sleep(50);
		CString cs;
		static int n = 0;
		for (int i = 0; i < 2; i ++)
			cs.Format(_T("this is a test. %d, this is a test. %d\n"), n, n++);
	}
}