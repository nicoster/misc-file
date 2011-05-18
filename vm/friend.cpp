class foo
{
	int n;
	friend void setn(foo& f){f.n = 0;}
};

//void setn(foo& f){f.n = 0;}

void main()
{
	foo f;
	setn(f);
}