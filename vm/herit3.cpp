#include "common.h"
typedef wstring CTString;

struct foo
{
	int m;
};

template <class TBase>
class XmlParse : public TBase
{
	XmlParse(CTString const& xml, CTString const& root = L"");

	XmlParse(TBase const& t){*(TBase*) this = t;}
};

template<>
class XmlParse<foo> : public foo
{
public:
	XmlParse(CTString const& xml = L"", CTString const& root = L"")
	{
		m = 3;
	}
};


void main()
{
	XmlParse<foo> f;
	cout << sizeof(f);
}