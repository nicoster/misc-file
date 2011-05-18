#include <list>
#include <iostream>
using namespace std;

struct foo
{
	foo(int n) : member(n){}
//	bool operator<(foo const& rhs)
//	{
//		return member < rhs.member;
//	}
	int member;
};

typedef foo * fooptr;

bool operator<(fooptr & lhs, fooptr & rhs)
{
	//return lhs.member < rhs.member;
	return lhs->member < rhs->member;
}


//struct CBaseElementPtr
//{
//	bool operator<(foo const& rhs)
//	{
//		return member < rhs.member;
//	}
//
//	CBaseElement* mem;
//};
//
//list <CBaseElementPtr>;

void main(void)
{
//	foo initer[] = {1, 9, 3, 4, 5, 6, 7};
	list<foo*> li;

//	for (int i = 0; i < 7; ++ i)li.push_back(new foo(i));
	
	//li.sort();
}