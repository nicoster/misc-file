#include <sstream>
#include <iostream>
using namespace std;
void main()
{
	wstring str(L"8080");
	wstringstream iss;
	iss << str;
	unsigned short nPort;
	iss >> nPort;
	wstringstream(L"8080") >> (short&)nPort;
	cout << nPort;
}