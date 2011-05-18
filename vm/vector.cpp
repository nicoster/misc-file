#include <vector>
using namespace std;
vector<int*> v;

void main()
{
	v.push_back(new int(0xaaaa));
	v.push_back(new int(0xbbbb));
	v.push_back(new int(0xcccc));
	v.push_back(new int(0xdddd));
	v.push_back(new int(0xeeee));
	vector<int*>::iterator i = v.begin();
	i++;
	i++;
}