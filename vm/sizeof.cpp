#include <windows.h>
#include <iostream>
using namespace std;
struct foo
{
	foo() { n = 2;}
	int n;
	int n2;
};

void main(void)
{
	cout<<sizeof(int)<<sizeof(LONGLONG)<<endl;
	cout<<sizeof(foo);
}

