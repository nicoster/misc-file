#include <iostream>
using namespace std;

class abc;void del(abc *pobj){ delete pobj;}class abc{public: abc(){  cout<<"abc"<<endl; } virtual 
 ~abc(){  cout<<"~abc"<<endl; }};void main(){ abc *pobj = new abc; del(pobj);} 