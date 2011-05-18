#include "template_enum.h"

namespace a{
class cl
{
	template<class T>
	void func(T const& t, foo f = bar)
	{
		T t2 = t;
		int n = f;
	}
	
	void func2()
	{
		func((int)1);
	}
};
}

using namespace a;
void main()
{
	cl c;
}