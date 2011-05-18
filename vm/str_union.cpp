#include "common.h"

struct foo
{
	union
	{
		struct bar
		{
			string a, b, c, d, e, f;
		} b;
		string strs[sizeof(bar)/sizeof(string)];
	};
};

void main()
{
}
