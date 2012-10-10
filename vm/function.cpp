#include <iostream>
#include "boost/function.hpp"
#include "boost/bind.hpp"
bool some_func(int i,double d) {
  return i>d;
}

// int main() {
//   boost::function<bool (int,double)> f;
//   f=&some_func;
//   std::cout << f(10,1.1) << std::endl;
// 	return 0;
// }

using namespace boost;
struct demo_class
{
	int add(int a, int b){
		return a+b;
	}
};

int main(){
	demo_class sc;
	function<int (int, int)> func1;
	function<int (demo_class&, int, int)> func2;
	
	func1 = bind(&demo_class::add, &sc,_1,_2);
	std::wcout << 1;
	func2 = &demo_class::add;
	std::cout << func1(10,20) << func2(sc,10, 20) << std::endl;
}
