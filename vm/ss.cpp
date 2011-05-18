//#include <list>
template <class T>
class foo
{
	T dummy;
};

class bar
{
	static foo<bar> tmp;
	//static list
};