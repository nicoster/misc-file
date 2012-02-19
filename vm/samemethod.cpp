#include <iostream>
using namespace std;
struct foo 
{
	virtual void foo1(){cout << "foo\n";}
	virtual void foo2(){cout << "foo2\n";}
	
};

struct bar 
{
	virtual void foo1(){cout << "bar\n";}
	virtual void bar2(){cout << "bar2\n";}
};

struct zoo : public foo, public bar
{
	void foo1(){cout << "zoo\n";}
};

int main()
{
	cout << "start\n";
	zoo z;
	z.foo1();
	((foo&)z).foo1();
	((bar&)z).foo1();
}