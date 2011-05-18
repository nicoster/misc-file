#include <list>
#include <algorithm>
using namespace std;
void main(void)
{
	int dummy[] = {1,2,3,4,5};
	list<int> listn(dummy, dummy + 5);
	
	typedef list<int>::iterator Iter;
	list<Iter> listiter;
	
	for (Iter iter = listn.begin(); iter != listn.end(); ++ iter)
	{
		listiter.push_back(iter);
	}
	
	for_each(listiter.begin(), listiter.end(), listn.erase);
	
}