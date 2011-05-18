#include <string>
#include <iostream>
using namespace std;

void main()
{
	string str("asdfasdf");
	
	cout << (str.find("?") == string::npos);
}