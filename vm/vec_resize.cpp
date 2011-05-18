#include "common.h"

void main()
{
	vector<int> v;
	v.resize(2);
	
	v[1] = 2;
	cout << "a";
	cout << v.size();
	v[20] = 1;
	cout << "b";
	cout << v.size();
}