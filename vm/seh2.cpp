#include <iostream.h>

void main()
{
	__try
	{
		*(int*)0 = 0;
	}
	__except(1)
	{
		cout << "except" << endl;
	}
	//~ __finally
	//~ {
		//~ cout << "finally" << endl;
	//~ }
	
	cout << "exit\n";
}