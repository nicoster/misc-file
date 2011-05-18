#include "common.h"

struct foo
{
	void vf(){}
};

struct bar
{
	void vf(){}
};

struct zoo : public foo, public bar
{
};

void main()
{
	zoo().vf();
}
