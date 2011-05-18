#include <iostream>
#include <string>
#include <algorithm>
#include "boost/lambda/lambda.hpp"
#include "boost/lambda/casts.hpp"
#include "boost/lambda/if.hpp"
#include "boost/lambda/bind.hpp"

template <typename String,typename Integral>
  void is_it_long(const String& s,const Integral& i) {
    using namespace boost::lambda;
    (if_then_else(bind(&String::size,_1) < ll_static_cast<typename String::size_type>(_2),
//      var(std::cout) << "Quite short...\n",
      std::cout << var("Quite short...\n"),
      std::cout << constant("Quite long...\n")))(s,i);
  }

//~ template <typename String,typename Integral>
  //~ void is_it_long(const String& s,const Integral& i) {
    //~ using namespace boost::lambda;
    //~ (if_then_else(bind(&String::size,_1)<
      //~ ll_static_cast<typename String::size_type>(_2),
        //~ var(std::cout) << "Quite short...\n",
        //~ std::cout << constant("Quite long...\n")))(s,i);
//~ }


int main() {
  std::string s="Is this string long?";
  is_it_long(s,111u);
  is_it_long(s,4);
}
