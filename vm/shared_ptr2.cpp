#include "boost/shared_ptr.hpp"
#include <vector>
#include <iostream>
#include <cstdio>
#include <boost/bind.hpp>
//~ #include <boost/lambda/lambda.hpp>
//~ #include <boost/lambda/bind.hpp>
//~ using namespace boost::lambda;
using namespace boost;
using namespace std;


int main() {
  std::cout << 
    "shared_ptr example with a custom deallocator.\n"; 
  {
    FILE* f=fopen("c:\\accessfile.ini","r");
    if (f==0) {
      std::cout << "Unable to open file\n";
      throw "Unable to open file";
    }

	//~ bind(&fclose, _1)(f);
    boost::shared_ptr<FILE> 
      my_shared_file(f, bind(&fclose, _1));

    // Position the file pointer
    fseek(my_shared_file.get(),42,SEEK_SET);
  }
  std::cout << "By now, the FILE has been closed!\n";
}
