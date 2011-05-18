#include "common.h"
struct session_context
{
	session_context()
	{
		size_t offset = (size_t)&((session_context*)0)->port_;
		memset((char*)this + offset, 0, sizeof(*this) - offset);
	}
	
	string str;
	int
	port_,
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h;
};
 
void main()
{
	session_context s;
	int3;
}