#include <iostream>
using namespace std;
#pragma pack(push, 1)
class foo
{
//	foo* rf;
//	foo& pf;
//	char& rc;
//	int n;
};
#pragma pack(pop)

void main()
{
	const char & rn = 1;
	cout<<sizeof(rn)<<endl;
	cout<<sizeof(foo)<<endl;
	
	foo a;
	int n;
}