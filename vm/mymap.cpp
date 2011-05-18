#include <iostream>
#include <map>
#include <string>
using namespace std;

void main()
{
	map<int, string> is;
	is[1] = "one";
	is[2] = "two";
	
	map<int, int> ii;
	ii[1] = 1;
	ii[2] = 2;
	
	cout<<is.size()<<endl;
	
	cout<<ii[3]<<endl;
	
	cout<<"exit"<<endl;
}