#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
//#include <boost/lambda/lambda.hpp>
//#include <boost/lambda/bind.hpp>
#include <boost/utility.hpp>
#include <boost/lambda/detail/lambda_functor_base.hpp> 

using namespace std;
using namespace boost;
using namespace boost::lambda;
 
int foo(int x)
{
    return x+1;
}
 
int main()
{
    //~ int i = 7, j = 11;
    //~ cout<<(_1=1, _1+ i)(i)<<",";
    //~ cout<<i<<endl;
//    cout<<(_1 = 1, _1 + j)(i)<<","<<i<<endl;

    //~ vector<int> v(10);
    //~ vector<int*> vp(10); 
    //~ for_each(v.begin(), v.end(), _1=bind(rand));
 
    //~ for_each(v.begin(), v.end(), cout <<_1 <<'\t');
    //~ cout <<endl<<endl;
 
    //~ for_each(v.begin(), v.end(), _1 = bind(foo, _1));
    //~ transform(v.begin(), v.end(), vp.begin(), &_1);
 
    //~ sort(vp.begin(), vp.end(), *_1> *_2);
    //~ for_each(vp.begin(), vp.end(), cout <<constant('\n') <<*_1 );
    //~ cout <<endl;
     for (int i = 0; i < 5; i ++)
        (var(std::cout)<<GetTickCount())();
    (var(std::cout)<< "aaa" )();    
    return 0;
} 
