struct foo{};
	
template<class T>
void bar(T& t)
{
	
}
struct zoo
{
	template<class T>
	void bar2(T& t)
	{
		
	}
	void demo()
	{
		foo f;
		bar2(f);
	}
};

void main()
{
	foo f;
	bar(f);
	zoo z;
	z.demo();
}