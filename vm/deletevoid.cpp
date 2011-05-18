#include <iostream>

/*
	delete 一个 c++ 对象时不能进行指针类型转换. 
*/

using namespace std;
struct foo
{
	~foo(){cout<<"~foo\n";}
};

void main()
{
	foo* p = new foo;
	delete (void*)p;	// call        operator delete
	
	p = new foo;
	delete p;	// call        @ILT+70(foo::`scalar deleting destructor')
}