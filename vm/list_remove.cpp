#include "common.h"

void main()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	
	cout << l.size() << endl;
	
	l.remove(2);
	cout << l.size() << endl;
	
	
}