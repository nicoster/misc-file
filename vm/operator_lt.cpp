#include "common.h"

struct info
{
	info() : a(1), b(2){}
	int a, b;
		
	template<class LOG>
	LOG& operator << (LOG& log)
	{
		return log << a << ", " << b;
	}
		
};

//~ template<class LOG>
//~ LOG& operator << (LOG& log, info const& i)
//~ {
	//~ return log << i.a << ", " << i.b;
//~ }

void main()
{
	cout << info() << " " << 13;
}