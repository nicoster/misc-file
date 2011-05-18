#include "common.h"

struct foo
{
	virtual void zoo(){}
	int n;
};

struct bar : public foo
{
	int m;
};

void main()
{
	//~ bar b;
	//~ foo &f = b;
	//~ bar &b2 = dynamic_cast<bar&>(f);
	
	string s = "<message type='a'>asdf</message>";
	s.replace("<message", "<message from='b'");
	
}