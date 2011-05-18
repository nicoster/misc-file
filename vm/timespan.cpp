#include <afx.h>
#include <afxcmn.h>
#include <iostream.h>

void main()
{
	CTimeSpan span = CTime(1999, 2, 1, 0, 0, 0) - CTime(1999, 1, 1, 0, 0, 0);
	cout<<span.GetTotalHours()<<","<<span.GetMinutes()<<","<<span.GetSeconds();
}