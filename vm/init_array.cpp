#include "common.h"

void main()
{
	int ints[10] = {1, 2, 3, 4};
	for (int i = 0; i < sizeof(ints) / sizeof(int); ++ i)
		cout << ints[i] << endl;
}