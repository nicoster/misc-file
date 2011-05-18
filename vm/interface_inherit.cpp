#include "common.h"


struct IFoo
{
	virtual void a(void) = 0;
};

struct IBar : public IFoo
{
	virtual void b(void) = 0;
};

struct Foo : public IFoo
{
	void a(void){}
};

struct Bar : public IBar, public Foo
{
	void b(void){}
};


void main()
{
	Bar b;
}