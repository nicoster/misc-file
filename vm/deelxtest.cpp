#define UNICODE
#define _UNICODE
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include "deelx.h"
#include <string>
#include <crtdbg.h>
#include <atlconv.h>
#include <vector>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

string s2 = "<?xml version=\"1.0\" encoding=\"UTF8\"?> <wbxapi><response><result>SUCCESS</result></response><securityContext><cred>W014MtehicQBxKZdzy6Am_c3000</cred></securityContext></wbxapi>";


typedef wstring CTString;
CTString Regreplace(CRegexpW const& reg, CTString const& strSrc, CTString const& strReplacePattern)
{
	CTString strRet;
	wchar_t* pstr = reg.Replace(strSrc.c_str(), strReplacePattern.c_str());
	strRet = pstr;
	reg.ReleaseString(pstr);
	return strRet;
}
#define APHELPER_API 

APHELPER_API wstring apHelper_AddWebexLinkPattern(wstring const& strSrc, wstring const& strReplacePatternConst) 
{
	static CRegexpW reg1(L"(?:.*CMD\\(\\d+:\\d+\\).*)|(?:<a\\s.*?>.*?</a>)|(?:<.*?>)", IGNORECASE);
	static CRegexpW reg2(L"\\s(webex)\\s", IGNORECASE);

	wstring strRet/*, strSrc(strSrcConst)*/;
	wstring strReplacePattern = L" " + strReplacePatternConst+ L" ";
	
	int nEnd = 0;
	while (1)
	{
		MatchResult mr = reg1.Match(strSrc.c_str(), nEnd);
		
		if (! mr.IsMatched())
		{
			wstring strTemp(strSrc.c_str() + nEnd);
			if (! strTemp.empty())
			{
				strTemp = L" " + strTemp + L" ";
				strTemp = Regreplace(reg2, strTemp.c_str(), strReplacePattern);
				strRet += strTemp.substr(1, strTemp.length() - 2);
			}
			return strRet;
		}
		
		wstring strTemp(strSrc, nEnd, mr.GetStart() - nEnd);
		if (! strTemp.empty())
		{
			strTemp = L" " + strTemp + L" ";
			strTemp = Regreplace(reg2, strTemp.c_str(), strReplacePattern);
			strRet += strTemp.substr(1, strTemp.length() - 2);
		}
		
		strRet += wstring(strSrc, mr.GetStart(), mr.GetEnd() - mr.GetStart());
		nEnd = mr.GetEnd();
	}
}

APHELPER_API wstring apHelper_AddWebexLink(wstring const& strSrc, wstring const& strLink)
{
	wostringstream oss; 
	oss << L"<a href=\"" << strLink << L"\" target=\"_self\" class=\"webexMeeting\" onmouseover=\"mouseOver(this)\" onmouseout=\"mouseOut(this)\" onmousedown=\"mouseDown(this)\" onmouseup=\"mouseOver(this)\">$0<font face=\"webdings\">6</font></a>";
	const wstring strReplacePattern = oss.str();

	return apHelper_AddWebexLinkPattern(strSrc , strReplacePattern) ;	
}

CRegexpW /*StringUtil::*/s_regPhoneNumber
// (L"((?<!\\d)\\+\\d{11}(?!\\d))|((?<!\\d)\\+\\d{2} \\(\\d{2}\\) \\d{3} \\d{4}(?!\\d))|((?<!\\d)\\+\\d{2}\\(\\d{2}\\)\\d{7}(?!\\d))|((?<!\\d)\\+\\d{2} \\(\\d{2}\\) \\d{3}-\\d{4}(?!\\d))|((?<!\\d)\\d{2} \\(\\d{2}\\) \\d{3} \\d{4}(?!\\d))|((?<!\\d)\\d{2}\\(\\d{2}\\)\\d{7}(?!\\d))|((?<!\\d)\\+?\\d{10}(?!\\d))|((?<!\\d)\\+\\d \\d{9}(?!\\d))|((?<!\\d)\\+?\\d\\(\\d{3}\\)\\d{6}(?!\\d))|((?<!\\d)\\+?\\d ?\\(\\d{3}\\) \\d{3} \\d{3}(?!\\d))|((?<!\\d)\\+?\\d-\\d{3}-\\d{3}-\\d{3}(?!\\d))|((?<!\\d)\\+?\\d ?\\(\\d{3}\\) \\d{3}-\\d{3}(?!\\d))|((?<!\\d)\\+?\\d(?: \\d{3}){3}(?!\\d))|((?<!\\d)\\+?\\d(?:\\.\\d{3}){3}(?!\\d))|((?<!\\d)\\d{9}(?!\\d))|((?<!\\d)\\(\\d{3}\\)\\d{6}(?!\\d))|((?<!\\d)\\(\\d{3}\\) \\d{3} \\d{3}(?!\\d))|((?<!\\d)\\d{3}-\\d{3}-\\d{3}(?!\\d))|((?<!\\d)\\(\\d{3}\\) \\d{3}-\\d{3}(?!\\d))|((?<!\\d)\\d{3} \\d{6}(?!\\d))|((?<!\\d)\\d{3} \\d{3} \\d{3}(?!\\d))|((?<!\\d)\\d{3}\\.\\d{3}\\.\\d{3}(?!\\d))|((?<!\\d)\\d{8}(?!\\d))|(\\d{2}-\\d{6}(?!\\d))|((?<!\\d)\\d{7}(?!\\d))|((?<!\\d)\\d{3}-\\d{4}(?!\\d))|((?<!\\d)\\d{4,6}(?!\\d))");

// (L"((?<!\\d)\\+\\d{11}(?!\\d))|(\\d{4})");

//(L"(?:(?<!\\d)\\+?\\d ?\\d{10}(?!\\d))|(?:(?<!\\d)\\+?\\d\\d ?\\(\\d\\d\\) ?\\d{3}[ -]?\\d{4}(?!\\d))|(?:(?<!\\d)\\+?\\d ?\\(\\d{3}\\) ?\\d{3}[ -]?\\d{4}(?!\\d))|(?:(?<!\\d)\\+?\\d[ .-]?\\d{3}[ .-]?\\d{3}[ .-]?\\d{4}(?!\\d))|(?:(?<!\\d)\\d{3}[ -.]?\\d{3}[ -.]?\\d{4}(?!\\d))|(?:(?<!\\d)\\(\\d{3}\\) ?\\d{3}[- ]?\\d{4}(?!\\d))|(?:(?<!\\d)\\d{3}-?\\d{6}(?!\\d))|(?:(?<!\\d)\\d\\d-?\\d{6}(?!\\d))|(?:(?<!\\d)\\d\\d-?\\d{5}(?!\\d))|(?:(?<!\\d)\\d{3}-?\\d{4}(?!\\d))|(?:(?<!\\d)\\d{3,6})(?!\\d)");
(L"(?:(?<!\\d)\\+?\\d ?\\d{10}(?!\\d))|(?:(?<!\\d)\\+?\\d\\d ?\\(\\d\\d\\) ?\\d{3}[ -]?\\d{4}(?!\\d))|(?:(?<!\\d)\\+?\\d ?\\(\\d{3}\\) ?\\d{3}[ -]?\\d{4}(?!\\d))|(?:(?<!\\d)\\+?\\d[ .-]?\\d{3}[ .-]?\\d{3}[ .-]?\\d{4}(?!\\d))|(?:(?<!\\d)\\d{3}[ -.]?\\d{3}[ -.]?\\d{4}(?!\\d))|(?:(?<!\\d)\\(\\d{3}\\) ?\\d{3}[- ]?\\d{4}(?!\\d))|(?:(?<!\\d)\\d{3}-?\\d{6}(?!\\d))|(?:(?<!\\d)\\d\\d-?\\d{6}(?!\\d))|(?:(?<!\\d)\\d\\d-?\\d{5}(?!\\d))|(?:(?<!\\d)\\d{3}-?\\d{4}(?!\\d))|(?:(?<!\\d)\\d{3,6}(?!\\d))");


/* nick 08-1-9 11:08  
	ignore <a>..</a>, <...>, :xxxx, #xxxx
	replace #xxxx# with xxxx
*/
wstring /*StringUtil::*/AddPhoneNumberLink(wstring const& strSrc, wstring const& strLink, wstring const& strBuddyName, wstring const& strTitle)
{
	static CRegexpW reg1(L"(?:.*CMD\\(\\d+:\\d+\\).*)|(?:<a\\s.*?>.*?</a>)|(?:<.*?>)|(?::\\d*)|(#\\d+#)", IGNORECASE), reg3(L"#(\\d+)#");
	CRegexpW& reg2 = s_regPhoneNumber;
	
	wostringstream oss;
 	oss << L"<a href=\"" << strLink << L"|$0;" << strBuddyName << L"\" title=\"" << strTitle << L"$0\" target=\"_self\" style=\"color:#0066CC; font-size:8pt; font-family:Tahoma; text-decoration: none; border-bottom:1px dashed\">$0</a>";

	const wstring strReplacePattern = oss.str();

	wstring strRet;
	
	int nEnd = 0;
	while (1)
	{
		MatchResult mr = reg1.Match(strSrc.c_str(), nEnd);
		
		if (! mr.IsMatched())
		{
			strRet += Regreplace(reg2, strSrc.c_str() + nEnd, strReplacePattern);
			break;
		}
		
		wstring strTemp(strSrc, nEnd, mr.GetStart() - nEnd);
		strRet += Regreplace(reg2, strTemp, strReplacePattern);
		
		strRet += wstring(strSrc, mr.GetStart(), mr.GetEnd() - mr.GetStart());
		nEnd = mr.GetEnd();
	}

	return Regreplace(reg3, strRet, L"$1");
}

wstring /*StringUtil::*/AddEmailTag(wstring const& strSrc)
{
#define EMAIL_PATTERN L"\\w+(\\.\\w+)*@\\w+(\\.\\w+)+"
	static CRegexpW reg1(L"(?:.*CMD\\(\\d+:\\d+\\).*)|(?:<a\\s.*?>.*?</a>)|(?:<.*?>)", IGNORECASE);
	static CRegexpW reg2(EMAIL_PATTERN);
	static wchar_t* strReplacePattern = L"<a href=\"mailto:$0\">$0</a>";
	
	wstring strRet;
	
	int nEnd = 0;
	while (1)
	{
		MatchResult mr = reg1.Match(strSrc.c_str(), nEnd);
		
		if (! mr.IsMatched())
		{
			strRet += Regreplace(reg2, strSrc.c_str() + nEnd, strReplacePattern);
			//~ wchar_t* pstr = reg2.Replace(strSrc.c_str() + nEnd, strReplacePattern);
			//~ strRet += pstr;
			//~ reg2.ReleaseString(pstr);
			return strRet;
		}
		
		wstring strTemp(strSrc, nEnd, mr.GetStart() - nEnd);
		strRet += Regreplace(reg2, strTemp.c_str(), strReplacePattern);
		//~ wchar_t* pstr = reg2.Replace(strTemp.c_str(), strReplacePattern);
		//~ strRet += pstr;
		//~ reg2.ReleaseString(pstr);
		
		strRet += wstring(strSrc, mr.GetStart(), mr.GetEnd() - mr.GetStart());
		nEnd = mr.GetEnd();
	}
}

BOOL ParseWapiURL(IN OUT CTString & strUrl)
{
	static CRegexpW reg(L"(.*?)//(?:(\\d{1,3}(?:\\.\\d{1,3}){3})|(.*?))/(.*)");
	MatchResult mr = reg.Match(strUrl.c_str());
	
	if (! mr.IsMatched()) return FALSE;
		
	// got group 2, it must be the ip address already.
	if (mr.GetGroupStart(2) > 0)
	{
		return TRUE;
	}
	
	CTString const& strDomainName = strUrl.substr(mr.GetGroupStart(3), mr.GetGroupEnd(3) - mr.GetGroupStart(3));
	USES_CONVERSION;
	hostent* phost = gethostbyname(W2A(strDomainName.c_str()));
	if (! phost) return FALSE;

	char* paddr = inet_ntoa(*(in_addr * )phost->h_addr);
	CTString strReplace =  L"$1//";
	strReplace += A2W(paddr);
	strReplace += L"/$4";

	strUrl = Regreplace(reg, strUrl, strReplace);
	return TRUE;
}

wstring toaddlink(L"<html><body>User &quot;percyw@sz.webex.com&quot; has invited you to a sharing session. Click <a href=\"https://172.16.196.240/tricon/jm.php?PWD=&amp;MK=31016099&amp;FN=Tinaz@sz.webex.com&amp;LN=*&amp;SN=Tinaz@sz.webex.com\">here</a> to accept.</body></html>");

// <font color=#000000>as5678df</font><a href=#>0000000</a> 192.168.0.1:10000  ##123235#<font color=#000000>as123df</font>
void main()
{
	//~ int n = 0;
	//~ vector<int> v2, & v = n ? vector<int>() : v2;
	//~ apHelper_AddWebexLink(L"<html>webex</html>webeax<b> webex <c> webex.", L"#");
	
//~ //	CRegexpW reg(L"\\([^\\]*)\\.png");
	//~ wstring str33 = L"\\w234232222222222223.png";
	//~ int nStart = str33.rfind(L"\\");
	//~ cout << nStart;
	//~ int nEnd = str33.rfind(L".");
	//~ cout << nEnd;
	//~ wstring str22(str33, nStart + 1, nEnd - nStart - 1);
	//~ wcout << str22;
//~ //	wcout << str33.substr(nStart + 1, nEnd - nStart - 1).c_str();
	//~ return;

	//~ //wcout << AddWebexLink(L"sd webex aswebexdf") << endl;
	//~ return;
	
	//~ WSAStartup(MAKEWORD(2, 2), (LPWSADATA)&WSAData());
	//~ CTString str32(L"http://www.163.com/wbxconnect/op.do");
	//~ ParseWapiURL(str32);
	//~ wcout << str32;
	//~ return;
	//~ wcout << AddEmailTag(toaddlink) << endl;
	//~ return;
	
	//~ _asm int 3;
	wstring str5(L"123+31421234567123 I have got a number +31 (42) 123 45674  +31(42)1234567  <font color=#000000>+31 (42) 123-4567      31 (42) 123 4567  31(42)1234567      +1408566123  +1 408566123  +1(408)566123  +1(408) 566 123  +1 (408) 566 123  +1-408-566-123  +1(408) 566-123  +1 (408) 566-123  <a href=#>+1 408 566 123  </a> 192.168.0.1:10000  ##123235#<font color=#000000>adf+1.408.566.123suffix</font>  asdfasdfasdfasdf    1408566123  1(408)566123 asdfasdf 1(408) 566 123  1 (408) 566 123  1-408-566-123  1(408) 566-123  1 (408) 566-123  1 408 566 123  1.408.566.123    408566123  (408)566123  (408) 566 123  (408) 566 123  408-566-123  (408) 566-123  (408) 566-123  408 566123  408 566 123  408.566.123    85661234  85-661234      5661234  566-1234    661234    61234    1234  ");
	
	
	wstring str6(L"+31421234567qwerty+31 (42) 123 4567qwerty+31(42)1234567qwerty+31 (42) 123-4567qwertyqwertyqwerty31 (42) 123 4567qwerty31(42)1234567qwertyqwertyqwerty+14085661234qwerty+1 4085661234qwerty+1(408)5661234qwerty+1(408) 566 1234qwerty+1 (408) 566 1234qwerty+1-408-566-1234qwerty+1(408) 566-1234qwerty+1 (408) 566-1234qwerty+1 408 566 1234qwerty+1.408.566.1234qwertyqwertyqwerty14085661234qwerty1(408)5661234qwerty1(408) 566 1234qwerty1 (408) 566 1234qwerty1-408-566-1234qwerty1(408) 566-1234qwerty1 (408) 566-1234qwerty1 408 566 1234qwerty1.408.566.1234qwertyqwerty4085661234qwerty(408)5661234qwerty(408) 566 1234qwerty(408) 566 1234qwerty408-566-1234qwerty(408) 566-1234qwerty(408) 566-1234qwerty408 5661234qwerty408 566 1234qwerty408.566.1234qwertyqwerty585661234qwerty585-661234qwertyqwerty85661234qwerty85-661234qwertyqwertyqwerty5661234qwerty566-1234qwerty56-61234qwertyqwerty661234qwertyqwerty61234qwertyqwerty1234qwerty");
	
	wstring str7(L"+1408 566.1234+1408 566-1234+1408 566 1234+1408 5661234+1408 566.1234+1408-5661234+1408-566.1234+1408-566-1234+1408-566 1234+1408-5661234+1408.5661234+1408.566.1234+1408.566-1234+1408.566 1234+1 408 566.1234+1 408 566-1234+1 408 566 1234+1 408 5661234+1 408 566.1234");
	
	wstring str8(L"<font>12</font>");
	wcout << AddPhoneNumberLink(str8, L"wbx:", L"nickx", L"Click to call ") << endl;
	return;
	
	CRegexpW reg(_T("\\w+@\\w+(\\.\\w+)+"));
	wstring str = L"adasd aa3dd@a.com.cn.cn.cn aadfasd@adfsd78dd.com";
	wcout << reg.Replace(_T("adasd aa3dd@a.com.cn.cn.cn aadfasd@adfsd78dd.com"), _T("<a href=\"mailto:$0\">$0</a>")) << endl;
	
	//~ CRegexp reg2(_T("A"), IGNORECASE);
	//~ wcout << reg2.Replace(_T("a"), _T("b"));
	
	//~ wstring s = L"b";
	//~ wcout<<s.compare(L"b");
	
	static CRegexpA reg3("encoding=\"([\\w\\-]+)\"", IGNORECASE);
	//~ cout << s2.length() << s2.c_str();
	MatchResult mr = reg3.Match(s2.c_str());
	//~ cout << mr.IsMatched() << endl;
	int start = mr.GetGroupStart(1);
	int end = mr.GetGroupEnd(1);
	
	//~ cout<< start << "," << end << endl;
	wstring str4 = L"a<     a    href  =   \"mAilto: a@a.com\"><font a asfasdf><B> mail me </B></font></A> a@a.a b <a href=mailto:a@a.a>aa</a> adj;s";
	wcout<<AddEmailTag(str4)<<endl;
}

