class foo
{
	public:
	void test(){}
};

enum
{
	foo,
};

void main(void)
{
	typedef class foo clsfoo;
	clsfoo *p = new clsfoo;
	p->test();
}