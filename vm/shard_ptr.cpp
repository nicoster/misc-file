#include "boost/shared_ptr.hpp"
#include <vector>
#include <iostream>
//#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
using namespace boost;
using namespace boost::lambda;
using namespace std;

class A {
public:
  virtual void sing()=0;
protected:
  //~ virtual 
	~A() {cout<<"~A\n";};
};

class B : public A {
public:
  virtual void sing() {
    std::cout << "Do re mi fa so la";
  }
  ~B(){cout<<"~B\n";}
};

boost::shared_ptr<A> createA() {
  boost::shared_ptr<A> p(new B());
  return p;
}

int main() {
  typedef std::vector<boost::shared_ptr<A> > container_type;
  typedef container_type::iterator iterator;

  container_type container;
  for (int i=0;i<10;++i) {
    container.push_back(createA());
  }
  
  for_each(container.begin(), container.end(), (bind(&A::sing, bind(&shared_ptr<A>::operator ->, _1)), std::cout<<var("\n")));
//  for_each(container.begin(), container.end(), bind(&A::sing, _1));

  //~ std::cout << "The choir is gathered: \n";
  //~ iterator end=container.end();
  //~ for (iterator it=container.begin();it!=end;++it) {
    //~ (*it)->sing();
  //~ }
}

