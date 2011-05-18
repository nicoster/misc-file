#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "boost/lambda/lambda.hpp"
#include "boost/lambda/bind.hpp"
#include "boost/lambda/if.hpp"

int main() {
  using namespace boost::lambda;

  std::vector<std::string> vec;
  vec.push_back("Lambda");
  vec.push_back("expressions");
  vec.push_back("really");
  vec.push_back("rock");

  std::for_each(vec.begin(),vec.end(),if_then_else(
    bind(&std::string::size,_1)<=6u,
      std::cout << _1 << '\n',
      std::cout << constant("Skip.\n")));

  std::for_each(vec.begin(),vec.end(),
    if_(bind(&std::string::size,_1)<=6u) [
      std::cout << _1 << '\n'
    ]
    .else_[
      std::cout << constant("Skip.\n")
    ] );
	
	(if_(_1<5) [std::cout << constant("Less than 5")])(make_const(3));
}
