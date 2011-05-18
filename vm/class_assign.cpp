#include "common.h"

struct zoo
{
	int i,j;
};
struct zoo2
{
	int i2,j2;
};

template<class T>
struct bar2 : public zoo2
{
	char x2,y2,z2;
};

template<class T>
struct bar : public zoo
{
	char x,y,z;
};
struct foo : public bar<foo>, public bar2<foo>
{
	int a,b,c,d;
	string e,f,g;
};

void main()
{
	foo f, f2;
	f = f2;
}