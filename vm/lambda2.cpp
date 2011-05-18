#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include "boost/lambda/lambda.hpp"
#include "boost/lambda/bind.hpp"

int main() {
  using namespace boost::lambda;

  typedef std::map<int,std::string> type;
  type keys_and_values;
  keys_and_values[3]="Less than pi";
  keys_and_values[42]="You tell me";
  keys_and_values[0]="Nothing, if you ask me";

  std::cout << "What's wrong with the following expression?\n";
  std::for_each(
    keys_and_values.begin(),
    keys_and_values.end(),
    std::cout << "key=" <<
      bind(&type::value_type::first,_1) << ", value="
        << bind(&type::value_type::second,_1) << '\n');

  std::cout << "\n...and why does this work as expected?\n";
  std::for_each(
    keys_and_values.begin(),
    keys_and_values.end(),
    std::cout << constant("key=") <<
      bind(&type::value_type::first,_1) << ", value="
        << bind(&type::value_type::second,_1) << '\n');

  std::cout << '\n';
  // Print the size and max_size of the container
  (std::cout << "keys_and_values.size()=" <<
    bind(&type::size,_1) << "\nkeys_and_values.max_size()="
      << bind(&type::max_size,_1))(keys_and_values);
}

