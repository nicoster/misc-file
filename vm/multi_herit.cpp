struct foo
{
	foo(int n){}
};

struct bar : public foo, public foo
{
	bar() : foo(1), foo(2){}
};

void main(){}