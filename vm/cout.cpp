#include <map>   
#include <string>   
#include <iterator>   
#include <iostream>   
   
using namespace std;   
namespace std      
{      
     //如果不将该函数放入名字空间std则使用ostream_iterator不能通过编译   
     //但是可以直接用cout输出pair   
   
    //~ template<class _Elem,class _Traits,class K,class V>   
    //~ basic_ostream<_Elem,_Traits>& operator<<(   
        //~ basic_ostream<_Elem,_Traits>& s   
        //~ ,   
        //~ const pair<K,V>& p   
        //~ )   
    //~ {   
        //~ return s<<p.first<<" : "<<p.second;   
    //~ }   
   
}   
   
template<class _Elem,class _Traits,class K,class V>   
basic_ostream<_Elem,_Traits>&  operator<<(   
    basic_ostream<_Elem,_Traits>& s   
    ,    
    const map<K,V>& m   
)   
{   
    copy(m.begin(), m.end(), ostream_iterator<pair<K,V> >(s, "\n"));   
    return s;   
}   
   
int main()   
{   
    using namespace std;   
    map<string,string> a;   
    a["key1"]="value1";   
    a["key2"]="value2";   
    cout<<a;   
//    system("pause");   
    return 0;   
}   
