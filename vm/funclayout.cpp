#include <stdio.h>
#include <iostream>
using namespace std;

struct foo
{
	int dummy(){return 0;}
	
	int n;
	int n2;
};

int main()
{
//    int foo::* n2 = &foo::n2;
//	int foo::* n = &foo::n;
	printf("%d, %d\n", &foo::dummy, &foo::n2);
	cout<<&foo::n2<<endl;
	return 0;
}
