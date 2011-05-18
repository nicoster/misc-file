#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;

void main()
{
	string str("");
	cout << strtol(str.c_str(), 0, 10);
}