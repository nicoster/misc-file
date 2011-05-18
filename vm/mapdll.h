#pragma warning(disable: 4786)
#include <map>

typedef std::map<int, int> map;
struct foo{map map_;};
void MAPAPI func(map& m);
void MAPAPI func2(map& m);