#include <iostream.h>
class foo
{
	public:
	~foo(){cout<<"foo\n";}
};

class bar : public foo
{
	public:
	~bar(){cout<<"bar\n";}
};

void main(void)
{
	foo *f = new bar;
	
	delete f;
}