#define UNICODE
#define _UNICODE
#include "common.h"

struct mystring : public wstring
{
	mystring(wstring const& rhs = wstring()) : wstring(rhs) {}
	virtual ~mystring(){}
};

typedef BOOL (*CryptProc)(const mystring &inString,mystring &outString,BOOL bEncrypt);

int show_value(CRegKey& reg, CryptProc Crypt)
{
	wchar_t buf[MAX_PATH] = {0};
	DWORD len = MAX_PATH - 1;
	LONG ret = reg.QueryStringValue(L"SSO_ORG_NAME", buf, &len);
//	CHK_RET(ret == ERROR_SUCCESS, "failed to query key.");
	mystring str;
	if (len)
	{
		Crypt(wstring(buf), str, FALSE);
		wcout << L"\tOrg Name: " << str << L"\t[" << buf << L"]" << endl;
	}
	else
		cout << "\tOrg Name: N/A\n";

	ZeroMemory(buf, MAX_PATH);
	len = MAX_PATH - 1;
	ret = reg.QueryStringValue(L"PARTNER_ORG_NAME", buf, &len);
//	CHK_RET(ret == ERROR_SUCCESS, "failed to query key.");
	if (len)
	{
		Crypt(wstring(buf), str, FALSE);
		wcout << L"\tPartner Name: " << str << L"\t[" << buf << L"]" << endl;
	}
	else
		cout << "\tPartner Name: N/A\n";
	
	return 0;
}

int main(int argc, char** argv)
{
    cout << "ssoutil v1.10 - Set SSO Org Name\n"
        "Copyright (C) 2009 Nick Xiao (nickx@sz.webex.com)\n"
        "Webex - www.webex.com\n\n";
	cout << "Usage:\n\t" << argv[0] << " [SSO_ORG_NAME [PARTNER_ORG_NAME [/c5]]]\n\n";
    
	HINSTANCE h = LoadLibraryA("aputil.dll");
	CHK_RET(h, "no aputil.dll found. place " << argv[0] << " into the Connect installation folder and try again.");
	
	CryptProc Crypt = (CryptProc)GetProcAddress(h, "?SSOInfo_AES_Encrypt@@YAHABV?$CStringT@_W@@AAV1@H@Z");
	CHK_RET(Crypt, "no encrypt proc found."); 
	
	USES_CONVERSION;
	wstring orgname, partname;
	bool c5 = false;
	switch(argc)
	{
	case 4:
		c5 = true;
	case 3:
		partname = A2W(argv[2]);
	case 2:
		orgname = A2W(argv[1]);
	}
	
	CRegKey reg;
	LONG ret = reg.Open(HKEY_LOCAL_MACHINE, c5 ? L"SOFTWARE\\AIM\\AIMPro" : L"SOFTWARE\\Cisco Systems, Inc.\\WebEx Connect");
	CHK_RET(ret == ERROR_SUCCESS, "failed to open reg key");
	
	cout << "Previous Settings: " << endl;
	CHK_RET(0 == show_value(reg, Crypt), "");
	
	if (! orgname.empty())
	{
		mystring str;
		CHK_RET(Crypt(orgname, str, TRUE), "failed to crypt org name");
		reg.SetStringValue(L"SSO_ORG_NAME", str.c_str());
	}
	
	if (! partname.empty())
	{
		mystring str;
		CHK_RET(Crypt(partname, str, TRUE), "failed to crypt org name");
		reg.SetStringValue(L"PARTNER_ORG_NAME", str.c_str());
	}
	
	if (argc > 1)
	{
		cout << endl << "New Settings: " << endl;
		CHK_RET(0 == show_value(reg, Crypt), "");
	}
	
	return 0;
}