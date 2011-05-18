#pragma warning(disable: 4786)
#include <windows.h>
#include <string>
#include <map>
using namespace std;

struct foo_t
{
	foo_t(string const& str="") /*: str_(str)*/{str_ = str;}
	string str_;
} foo("a");

map<int, foo_t> foos;

int bar(int a)
{
	int b = 0;
	b = GetTickCount() + a;
	return b;
}

void main()
{
	bar(4);
	foos[1] = foo_t("b");
	foo_t &foo2 = foos.begin()->second;
}

