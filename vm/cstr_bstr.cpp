#include <afxcmn.h>

void main()
{
	CString cs;
	BSTR bstr(L"nick");
	AfxMessageBox(CString(bstr));
}