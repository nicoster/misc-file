#include <iostream>

/*
	delete һ�� c++ ����ʱ���ܽ���ָ������ת��. 
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