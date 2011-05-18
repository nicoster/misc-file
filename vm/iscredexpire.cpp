#include "common.h"

wchar_t* resp = L"<?xml version='1.0' encoding='UTF-8'?> <wbxapi><messageStrings><message>wapi.expired_credential - Security credential has expired. You must log in again.</message></messageStrings><securityContext><cred>X04sEB_SJDhnKoMHWSCidj4wG00</cred></securityContext><response><result>FAILURE</result><exceptionID>wapi.expired_credential</exceptionID><reason>wapi.expired_credential - Security credential has expired. You must log in again.</reason></response></wbxapi>";

BOOL IsCredExpired2(wstring const& response)
{
	wstring const& starttag = L"<exceptionID>", endtag = L"</exceptionID>";
	size_t pos = response.find(starttag);
	if (pos == -1) return FALSE;
	pos += starttag.length();
	size_t pos2 = response.find(endtag, pos);
//	CHK_RET_FALSE(pos != -1);
	wstring const& expID = response.substr(pos, pos2 - pos);
	
	wcout << expID << endl;
	return FALSE;
}

void main()
{
	IsCredExpired2(resp);
}