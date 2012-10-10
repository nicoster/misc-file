#include <sstream>
#include <iostream>
using namespace std;
int main()
{
	wstring str(L"8080");
	wstringstream iss;
	iss << str;
	unsigned nPort;
	iss >> nPort;
	wstringstream(L"8080") >> nPort;
	cout << nPort;
	return 0;
}