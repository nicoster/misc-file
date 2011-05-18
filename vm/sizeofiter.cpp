#include "common.h"

void main()
{
	list<int> l;
	l.push_back(1);
	cout << sizeof(l.begin()) << endl;
	find(l.begin(), l.end(), 2);
}