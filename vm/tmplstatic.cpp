#include <iostream>
using namespace std;

template<class T>
struct foo
{
	static void test()
	{
		static T t;
		cout << &t;
	}
}

struct base
{
}