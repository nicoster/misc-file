#include <iostream>
#include <boost/format.hpp>
using namespace std;
using namespace boost;
void main()
{
     cout << boost::format("writing %1%,  x=%2% : %3%-th try") % "toto" % 40.23 % 50 <<endl; 
 
     format f("a=%1%,b=%2%,c=%3%,a=%1%");
     f % "string" % 2 % 10.0;
 
     cout << f.str() << endl;
}