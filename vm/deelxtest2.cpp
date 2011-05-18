#define UNICODE
#define _UNICODE
#include "common.h"
#include "regexp.h"

string src = "aasdfasdf\"exceptionID\": \"wapi.expired_credential\"asdfasdf";

bool isurl(wstring const& strURL)
{
	static CRegexpW reg(L"(https://|http://|mailto:|ftp://)?[\\w\\d_\\-.%!~'*()@]+(:\\d+)?(/[\\w\\d_\\-.%!~'*()@]*)*(\\?[\\w\\d_\\-./%&~'*;+:#=]*)?", IGNORECASE);

	return reg.MatchExact(strURL.c_str(), strURL.length()).IsMatched();
}

void main()
{
	cout << isurl(L"ftp://www.1!%~*(6)3.c@o'm/abc") << endl;
	cout << isurl(L"http://www.163.com:8080@/") << endl;
	cout << isurl(L"ftp://www.163.com:8080/") << endl;
	cout << isurl(L"mailto:nickx@sz.webex.com") << endl;
	cout << isurl(L"http://www.163.com:3333/a/b/c.php?a=b&c=d") << endl;
	return;
	//~ static CRegexp reg("\"(exceptionID\":\\s*\"(.*?))\"");		// "exceptionID":\s*"(.*?)"
	//~ MatchResult mr = reg.Match(src.c_str(), 0);
	//~ if (mr.IsMatched())
	//~ {
		//~ cout << RegGetGroup(src, mr, 1) << endl;
		//~ cout << RegGetGroup(src, mr, 2) << endl;
		//~ int start = mr.GetGroupStart(1), end = mr.GetGroupEnd(1);
		//~ cout << src.substr(start, end - start);
	//~ }
	
	//~ cout << RegReplace<char>(reg, src, "xxx") << endl;
}