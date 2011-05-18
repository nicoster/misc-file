#include <iostream>
#include <boost/assign/std/vector.hpp> // for 'operator+=()'
#include <boost/assert.hpp>
using namespace std;
using namespace boost::assign; // bring 'operator+=()' into scope


void main()
{
	vector<int> v;
	v += 1,2,3,4;
	vector<int>::const_iterator i;
	assert(v.end() == i);
	
}