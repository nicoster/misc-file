#include <iostream>
#include <string>
#include "boost/regex.hpp"
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

using namespace std;
using namespace boost;
using namespace boost::lambda;

int main() {
  //~ boost::regex reg("/");
  //~ std::string s="Split/Values/Separated/By/Slashes,";
  //~ std::vector<std::string> vec;
  //~ boost::sregex_token_iterator it(s.begin(),s.end(),reg,-1);
  //~ boost::sregex_token_iterator end;
  //~ while (it!=end) 
    //~ vec.push_back(*it++);

  //~ assert(vec.size()==std::count(s.begin(),s.end(),'/')+1);
  //~ assert(vec[0]=="Split");
  
  boost::regex reg4("[^13579]");
  std::string s="0123456789";
  boost::sregex_iterator it(s.begin(),s.end(),reg4);
  boost::sregex_iterator end;

  while (it!=end) 
    std::cout << *it++;
  
}
