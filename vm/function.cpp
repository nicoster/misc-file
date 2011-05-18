#include <iostream>
#include "boost/function.hpp"

bool some_func(int i,double d) {
  return i>d;
}

int main() {
  boost::function<bool (int,double)> f;
  f=&some_func;
  f(10,1.1);
}

