#include "common.h"


struct base
{
	~base(){cout << "~base";}
};

struct IDelete
{
	virtual ~ IDelete(){}
};

template<class T>
struct CDelete : public IDelete
{
	T t;
};

void main()
{
	IDelete* foo = new CDelete<base>;
	delete foo;
}