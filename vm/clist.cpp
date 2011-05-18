#include <afxtempl.h>
#include <iostream>

using namespace std;

void main(void)
{
	CList<CString , CString> strList;
	CString cs1 = "my";
	strList.AddTail(cs1);
	CString cs2 = "test";
	strList.AddTail(cs2);
	cout << strList.GetCount()<<endl;
}	