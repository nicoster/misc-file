#include <afxcmn.h>
#include <map>
#include <sstream>
#include <iostream>

using namespace std;
typedef map<CString, CString> COOKIES;
BOOL GetCookieList(CString const& csCookies, COOKIES & cookies)
{
    CString csTemp;
    int nStart = 0;
    int nPosAnd = 0;
    while ( nPosAnd < csCookies.GetLength())
    {
        nPosAnd = csCookies.Find(_T("&"), nStart);
        if (nPosAnd == -1) nPosAnd = csCookies.GetLength();
        int nPosEqual = csCookies.Find(_T("="), nStart);
        if (nPosEqual != -1 && nPosEqual < nPosAnd)
            cookies[csCookies.Mid(nStart, nPosEqual - nStart)] = csCookies.Mid(nPosEqual + 1, nPosAnd - nPosEqual - 1);
        nStart = nPosAnd  + 1;
    }
    return TRUE;
}

void main()
{
    COOKIES cookies;
    GetCookieList(_T("password=97a54a56a48a101a49a54a50a56a49a56a50a50a97a102a97&username=49a116a115a101a116a115a100a105&"), cookies);

    for (COOKIES::iterator i = cookies.begin(); i != cookies.end(); ++ i)
    {
        TRACE(i->first);
        TRACE("/");
        TRACE(i->second);
        TRACE("\n");
//		cout<<i->first<<","<<i->second;
    }
    
    CString cs = _T("105");
    stringstream ss;
    ss<<LPCTSTR(cs);
    int n;
    ss>>n;
    TCHAR ch = n;

    cout<<ch;
}