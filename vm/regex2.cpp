#include <iostream>
#include <string>
#include "boost/regex.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

using namespace std;
using namespace boost;
using namespace boost::lambda;


class regex_callback {
  int sum_;
public:
  regex_callback() : sum_(0) {}

//  template <typename T> void operator()(const T& what) {
  void operator()(const smatch& what) {
    sum_+=atoi(what[1].str().c_str());
  }

  int sum() const {
    return sum_;
  }
};


int main() {
  boost::regex reg("(\\d+),?");
  std::string s="123,1,2,3,5,8,13,21";

  boost::sregex_iterator it(s.begin(),s.end(),reg);
  boost::sregex_iterator end;

  regex_callback c;
  int sum=for_each(it,end,c).sum();

//    typedef ssub_match::value_type value_type;
    bind(&string::c_str(), bind(&ssub_match::str, bind(&smatch::operator[], _1, 1)))(*it);
	for_each(it, end, 
		cout<<bind(&ssub_match::str, bind(&smatch::operator[], _1, 1))<<"\n"
	);
//	std::cout<<sum;
}
