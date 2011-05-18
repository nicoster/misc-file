#include "common.h"

struct foo
{
	foo(string const& name) : name_(name){ cout << name_ << " ctor" << endl;}
	foo (foo const& f) { name_ = f.name_; cout << name_ << " copy ctor" << endl;}
	~foo() { cout << name_ << " dtor" << endl;}
	string name_;
};

foo bar(string const& name)
{
	foo f(name);
	return f;
}
void main()
{
	foo const&f = bar("a");
	cout << "after bar" << endl;
	
	foo f2 = bar("b");
	cout << "after bar2" << endl;
}