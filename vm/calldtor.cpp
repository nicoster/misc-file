#include <iostream.h>
class foo
{
public:
	~foo(){cout<<"in dtor"<<endl;}
	static calldtor(foo*p){p->~foo();}
};

void main()
{
	foo *p = new foo();
	foo::calldtor(p);
	p->~foo();
	delete (void*)p;
}

