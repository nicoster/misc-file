#include <afx.h>
#include <iostream.h>

void main()
{
	CTime tm(2007,2,31, 0, 0, 0);
	cout<<tm.Format(_T("%Y-%m-%d %H:%M:%S"));
}