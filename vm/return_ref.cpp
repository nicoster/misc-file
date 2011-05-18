#include "common.h"

char* const& foo()
{
	return "";
}
void main()
{
	cout << foo();
}