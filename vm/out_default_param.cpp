#include "common.h"

struct bar{};

void foo(bar& n = bar())
{
	//~ n.push_back(1);
}

void main()
{
	foo();
}