#include <windows.h>
#include <iostream.h>
struct foo
{
	foo(){
		static DWORD dw = GetTickCount();
		cout<<dw<<endl;
	}
	static int get()
	{
		static DWORD dw = GetTickCount();
		return dw;
	}
};

void main()
{
	foo f1;
	Sleep(100);
	cout<<"aaa"<<endl;
	foo f2;
}