//~ void fun(int, int) {
//~ }

//~ int main() {
	//~ fun(5, 10);
	//~ return 0;
//~ }

struct foo
{
	void dummy(int){};
};
void main()
{
	foo f; 
	f.dummy(5);
}