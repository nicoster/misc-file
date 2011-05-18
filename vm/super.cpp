struct foo
{
	int n;
};

class bar : public foo
{
	bar(){__super::n = 0;}
};

void main(){}