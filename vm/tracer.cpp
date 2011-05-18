#include <iostream>
#include <boost/bind.hpp>
using namespace std;
using namespace boost;

class tracer {
public:
  tracer() {
  std::cout << "tracer::tracer()\n";
}

tracer(const tracer& other) {
  std::cout << "tracer::tracer(const tracer& other)\n";
}

tracer& operator=(const tracer& other) {
  std::cout <<
    "tracer& tracer::operator=(const tracer& other)\n";
  return *this;
}

~tracer() {
  std::cout << "tracer::~tracer()\n";
}

void print(const std::string& s) const {
  std::cout << s.c_str() << '\n';
  }
};

void main()
{
	tracer t;
	boost::bind(&tracer::print,&t,_1)
	  (std::string("I'm called on a copy of t\n"));
	
}