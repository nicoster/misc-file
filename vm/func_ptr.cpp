
int* foo(int){return 0;}

typedef int* (*foo_ptr)(int);
void main()
{
	foo_ptr f = foo;
	f(1);
}