#include "common.h"

void main()
{
	ifstream in("d:\\wbxca.crt");
	string line, ret;
	getline(in, line);
	ret += line + "\n";

	getline(in, line);
	for(int i = 0; i < line.length();)
	{
		ret += line.substr(i, 64) + "\n";
		i += 64;
	}
	getline(in, line);
	ret += line;

	ofstream o("d:\\wbxca2.crt");
	o << ret;
}