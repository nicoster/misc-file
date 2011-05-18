#include <list>
#include <iostream>
using namespace std;

#if _MSC_VER > 1020   // if VC++ version is > 4.2
using namespace std;  // std c++ libs implemented in std
#endif


typedef list<int, allocator<int> > LISTINT;

void main()
{
  // List's must be sorted first
  int list1[] = {12,11,13,7,6,5,3,19};
  int list2[] = {22,21,20,10,7,6,50};

  LISTINT test1;
  LISTINT test2;
  LISTINT::iterator i;

  test1.insert (test1.begin(), list1, list1 + 8);
  test2.insert (test2.begin(), list2, list2 + 7);

  test1.merge (test2);

  // 22 21 20 12 11 10 10 7 7 6 6 5 5 3 1
  for (i = test1.begin(); i != test1.end(); ++i)
	 cout << *i << " ";
  cout << endl;
}
