#include <iostream>
using namespace std;

template<class T>
class foo
{
	public:
	void Connect()
	{
		T* pT = (T*)this;
		cout<<this<<endl;
		cout<<(T*)this<<endl;
		pT->DoConnect();
	}
};

class zoo{int n;};
class bar : public zoo, public foo<bar>
{
	public:
	void DoConnect(){cout<<"DoConnect in bar"<<endl;}
	int aaa;
};

void main()
{
	bar b;
	b.Connect();
}
