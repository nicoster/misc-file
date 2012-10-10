#include <sstream> //"common.h"
#include <iostream>
using namespace std;

int main()
{
	stringstream s;
	s << "3";
	int n = 1;
	s >> n;
	cout << n << endl;
	return 0;
}