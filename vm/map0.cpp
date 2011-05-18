#include <map>

void main()
{
	typedef std::map<int, int> map;
	map i, j;
	_asm int 3;
	i = j;
}