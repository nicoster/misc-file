#include <iostream>
#include <list>
using namespace std;

void main(void)
{
	list<int> li;
	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	
	//~ li.erase(li.begin());
	typedef list<int>::iterator  ITER
	list<int>::iterator iter = li.begin();
	list<ITER> 
	for(; iter != li.end(); iter++)
	{
		
	}
//		li.erase(iter);
	
	if (li.empty())
		cout<<"empty\n";
	else
		cout<<"not empty\n";
}