#include <iostream.h>
template <class T>
T fun()
{return T();}
	
void main()
{
	fun<int>();
	char a = -17;
	unsigned char c = a;
	a = c;
	cout<<int(a);
}