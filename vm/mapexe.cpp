#define MAPAPI _declspec(dllimport)
#include "mapdll.h"
#pragma comment(lib, "mapdll.lib")
void main()
{
	map m, n;
	func(m);
	func2(m);
	n = m;
	map i, j;
	i = j;
}