#include "common.h"

struct foo
{
	foo() : m_str("bbb"){}
	string m_str;
	string get_foo(){return m_str;}
};
	

void main()
{
	LPCTSTR sz = "aaaa";
	string str = sz;
	
	string str2 = str.c_str(), str3 = str;
	
	foo f;
	string str4 = f.get_foo().c_str();
}