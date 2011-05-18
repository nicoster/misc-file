#include <iostream>
class foo
{
public:
	void bar1()
	{
		std::cout<<"in bar1";
	}
	void bar2()
	{
		std::cout<<"in bar2";
	}		
	
	typedef void (__thiscall foo::*FUNC)(void);
	
	void zoo(FUNC func)
	{
		func();
	}
};

void main(void)
{
	foo dummy;
	dummy.zoo(foo::bar1);
}