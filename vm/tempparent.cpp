template <class T>
class foo
{
};

template <class T>
class bar : public foo<T>
{
};

void main()
{
	bar<bar> b;
}