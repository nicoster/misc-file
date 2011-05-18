#include <iostream>
#include <set>
using namespace std;

void main()
{
	char* p="abcde";	set<char> s(p,p+strlen(p));	cout << s.size() << endl;
}