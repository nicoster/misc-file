#include <windows.h>
#include <stdio.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")

BOOL EXCEPTION=0; //Exception flag.
class ExcepStackMsg //Create local variable of this class to record function info
{
	char* pmsg;
public:
	ExcepStackMsg(char *msg)
	{
		pmsg=(char*)malloc(strlen(msg)+1);
		strcpy(pmsg,msg);
	};
	~ExcepStackMsg()
	{
		if(EXCEPTION)
			printf("Exception happens: %s\n",pmsg);
		free(pmsg); 
	};
};
EXCEPTION_DISPOSITION
__cdecl
_except_handler(
				struct _EXCEPTION_RECORD *ExceptionRecord,
				void * EstablisherFrame,
				struct _CONTEXT *ContextRecord,
				void * DispatcherContext )
{
	EXCEPTION=1; 
	printf("got it\n");
	return ExceptionContinueSearch; //Allow C++ handler to run
}

void foo1()
{ 
	//printf("in foo1\n");
	//ExcepStackMsg e("foo1");
	throw 1; 
};
void foo2()
{
	//printf("in foo2\n");
	//ExcepStackMsg e("foo2");
	foo1(); 
};
void foo3()
{
	//printf("in foo3\n");
	//ExcepStackMsg e("foo3");
	foo2();
};
//DWORD WINAPI ThreadProc( LPVOID lpParameter)
DWORD main(void)
{
	
	DWORD myESP;
	void * test=_except_handler;
	DWORD handler = (DWORD)_except_handler;
	//_except_handler(0,0,0,0);
	printf("1\n");
	getchar();
	__asm
	{ 
		mov  myESP,ESP  //Save Stack register pointers
			push    _except_handler         // Address of handler function
			// push    test         // Address of handler function
			push    FS:[0]          // Address of previous handler
			mov     FS:[0],ESP      // Install new EXECEPTION_REGISTRATION
			// mov  FS:[0],100
	}
	try
	{
		printf("2\n");
		getchar();
		
		foo3();
	}
	catch(...)
	{
		EXCEPTION=0;
		printf("catch\n");
	};
	__asm
	{                           
		mov ESP,myESP   //Restore Stack register pointers
	}
	
	return 0;
}

