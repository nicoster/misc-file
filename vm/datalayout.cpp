#include <iostream>
using namespace std;

struct foo
{
	int n;
	int n2;
//	virtual void dummy(){}
};

struct bar : public foo
{
	int n;
};

int main()
{
	foo f;
	//cout<<&f.n<<endl;
	cout<<&foo::n<<endl;
	cout<<&foo::n2<<endl;
	//cout<<&bar::n<<endl;
	//cout<<sizeof(foo)<<endl;
	return 0;
}
