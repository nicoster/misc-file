#include <string>
#include <iostream>
using namespace std;

void main()
{
	const wstring & strTag = L"siteUrl=";
	wstring s(L"aaasitedUrl=bbbddddddd");
	
	int n = s.find(strTag);
	wcout << n << endl;
	wcout << s.substr(n + strTag.length()).c_str();
}