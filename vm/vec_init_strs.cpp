#include "common.h"

char *strs[] = {"a", "b"};

//vector<string> v(&strs[0], &strs[sizeof(strs)/sizeof(strs[0])]);

void main()
{
	cout << sizeof(strs)/sizeof(strs[0]);
}