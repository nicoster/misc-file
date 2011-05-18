#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include "boost/lambda/lambda.hpp"
#include "boost/lambda/construct.hpp"
#include "boost/lambda/bind.hpp"
#include "boost/lambda/if.hpp"
#include "boost/lambda/casts.hpp"
#include "boost/shared_ptr.hpp"

class base {
public:
  virtual ~base() {}
};

class derived : public base {
};

int main() {
  using namespace boost::lambda;

  typedef boost::shared_ptr<base> ptr_type;
  typedef std::map<std::string,ptr_type> map_type;

  map_type m;
  m["An object"]=ptr_type(new base);
  m["Another object"]=ptr_type();
  m["Yet another object"]=ptr_type(new base);

  std::for_each(m.begin(),m.end(),
    if_then_else(!bind(&ptr_type::get,
      bind(&map_type::value_type::second,_1)),
       (bind(&map_type::value_type::second,_1)=
         bind(constructor<ptr_type>(),bind(new_ptr<derived>())),
         var(std::cout) << "Created a new derived for \"" <<
           bind(&map_type::value_type::first,_1) << "\".\n"),
             var(std::cout) << "\"" <<
               bind(&map_type::value_type::first,_1)
                 << "\" already has a valid pointer.\n"));

  m["Beware, this is slightly tricky"]=ptr_type();
  std::cout << "\nHere we go again...\n";

  std::for_each(m.begin(),m.end(),
    if_then_else(!bind(&map_type::value_type::second,_1),
      ((bind(static_cast<void (ptr_type::*)(base*)>
        (&ptr_type::reset<base>),
       bind(&map_type::value_type::second,_1),
         bind(new_ptr<base>()))),
           var(std::cout) << "Created a new derived for \""
             << bind(&map_type::value_type::first,_1)
               << "\".\n"),
                 var(std::cout) << "\"" <<
                   bind(&map_type::value_type::first,_1)
                     << "\" already has a valid pointer.\n"));
}

