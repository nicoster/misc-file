#include "common.h"
typedef wstring CTString;

struct foo
{
	int m;
};

template <class TBase, class T>
class XmlParse : public TBase
{
	XmlParse(CTString const& xml, CTString const& root = L"");

	XmlParse(TBase const& t){*(TBase*) this = t;}
};

template<class T>
class XmlParse<foo, T> : public foo
{
public:
	XmlParse(CTString const& xml, CTString const& root = L"")
	{
		T* p = (T*)this;
		p->n = 2;
		foo::m = 3;
	}
};

struct bar : public XmlParse<foo, bar>
{
	bar() : XmlParse<foo, bar>(L""){}
	int n;
};


void main()
{
	bar b;
	cout << b.n << "," << b.m;
}