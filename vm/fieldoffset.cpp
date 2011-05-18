#include <iostream>
using namespace std;
struct foo
{
	int a;
	int c;
	int b;
	int e;
	
};
struct foo2
{
	int a;
	int c;
	int b;
	
};
struct bar : public foo, foo2
{
	int d;
};

#define FIELD_OFFSET(type, field)    ((long)(long)&(((type *)0)->field))
#define FIELD_OFFSET2(type, field)   ((unsigned long)(&type::field) - 1)
#define classoffset(base, derived) ((unsigned long)(static_cast<base*>((derived*)8))-8)
void main()
{
	cout<<FIELD_OFFSET(bar, d)<<endl;
	cout<<FIELD_OFFSET2(bar, d)<<endl;
	//~ cout<<classoffset(foo2, bar)<<endl;
}
