#include<iostream>
using namespace std;

class foo
	{
		public:
			
		foo(int n = 3):i(n){}
		
			int i;
			
	};
	
	void main()
	{
		
		foo test(3);
		cout << test.i <<endl;
	}