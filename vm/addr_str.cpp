#include <string>
#include <iostream>

using namespace std;
struct foo
{
	string str;
};

void main()
{
	string str;
	foo f;
	cout<<&str<<endl;
	cout<<&f.str<<endl;
}