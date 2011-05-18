struct dummy{};

template <class T>
struct foo : public T
{
	int n;
};

template <class T>
struct bar
{
	int get_n()
	{
	//	T* pThis = this;
	//	return pThis->n;
		return 0;
	}
};

//class zoo : foo<

void main()
{
	foo<bar<foo<dummy> > > f;
	f.get_n();
}

