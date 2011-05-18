class foo
{
public:
	void deleteme(){delete this;}
protected:
	int dummy;
};

void main(void)
{
	foo*p = new foo;
	p->deleteme();
	//~ int *p2=0;
	//~ *p2=0;
}
