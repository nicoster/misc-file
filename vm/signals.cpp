#include <iostream>
#include "boost/signals.hpp"
#include "boost/lambda/lambda.hpp"

void my_first_slot() {
  std::cout << "void my_first_slot()\n ";
}

class my_second_slot {
public:
  void operator()() const {
    std::cout <<
      "void my_second_slot::operator()() const\n ";
  }
};

int main() {
	using namespace boost::lambda;
  boost::signal<void ()> sig;

 	sig.connect(var(std::cout)<<"3rd\n ");
 sig.connect(&my_first_slot);
  sig.connect(my_second_slot());
	sig.connect(std::cout<<constant("4th\n"));

  std::cout << "Emitting a signal...\n ";
  sig();
}