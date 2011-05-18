struct foo
{
	int a,b,c;
	bool operator == (foo const& rhs)
	{
		return false;
	}
};

void main()
{
	foo f, f2;
	if (f == f2) 
	{
	}
}