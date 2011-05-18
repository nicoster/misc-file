#define parentheses operator()
struct foo
{
	int n_;
	foo(int n = 0) : n_(n){}
	int parentheses(int n){return n;}
	int operator+=(int n){return n_+=n;}
};

void main()
{
	foo f(2);
	foo(1);
	f.parentheses(1);
	f.operator()(1);
	f(1);
	f.operator+=(2);
	f+=2;
}