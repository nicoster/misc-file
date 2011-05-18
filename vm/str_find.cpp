#include <string>
#include <iostream>
using namespace std;

void main()
{
	string s("abcde");
	cout << s.find("bcsd") << endl;
	cout << string::npos;
}