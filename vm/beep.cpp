#include <windows.h>
void main(int argc,char *argv[])
{
//	__asm int 3;
	enum{FREQ = 0, ELAPSE, COUNT, INTERVAL};
	int nParams[4] = {4000, 50, 1, 100};
	while (argc -- > 1)
	{
			int nTemp = atoi(argv[argc]);
			if (nTemp > 0)
				nParams[argc - 1] = nTemp;
	}
	
	while(nParams[COUNT] -- > 0) 
	{
		Beep(nParams[FREQ], nParams[ELAPSE]);
		Sleep(nParams[INTERVAL]);
	}
}