#include <iostream.h>

void main()
{
	struct du
	{
		char by[8];
		union
		{
			char n;
			short s;
		};
	};
	cout<<sizeof(du);
}