#include <iostream>
#include <boost/assign.hpp>
#include <boost/assign/std/list.hpp>
#include <list>
#include <boost/bind.hpp>

using namespace std;
using namespace boost::assign;
using namespace boost;
void main()
{
	_asm int 3;
	list<int> v;
	v += 1, 2, 3, 4, 5, 6;
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 
	cout<<"\n";

	typedef list<int>::iterator iterator;
	for (iterator i = v.begin(); i != v.end();)
		i = v.erase(i);
	
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 
}