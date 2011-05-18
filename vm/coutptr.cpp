#include "common.h"

void main()
{
	int* p = new int (0);
	int n = (int)p;
	cout << hex << n << endl;
}