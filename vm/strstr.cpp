#include <stdlib.h>
#include <string.h>
#include <iostream.h>
void main()
{
	char RecvDataBuff[]="HTTP/1.1";	char* pt= strstr(RecvDataBuff,"/");
	cout << RecvDataBuff << endl;
	cout << pt << endl;	*pt='\0'; 
	
}