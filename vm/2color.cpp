#include <iostream>
#include <string>
#include "boost/regex.hpp"

int main()
{
    boost::regex reg("(Colo)(u)(r)",
                     boost::regex::icase|boost::regex::perl);

    std::string s="Colour, colours, color, colourize";

    s=boost::regex_replace(s,reg,"$1$3");
    std::cout << s;
}

