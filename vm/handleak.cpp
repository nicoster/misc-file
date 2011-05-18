#include "common.h"
 

 

void fun1(void);

void fun2(void);

void fun3(void);

void fun4(void);

 

int main(int argc, char* argv[])

{

      while(1)

      {

            fun1();

            fun2();

            Sleep(100);

      }

      return 0;

}

 

void fun1(void)

{

      fun3();

}

 

void fun2(void)

{

      fun4();

 

}

void fun3(void)

{

      HANDLE hEvent;

 

      hEvent = CreateEvent(NULL,TRUE,TRUE,NULL);

      CloseHandle(hEvent);

}

void fun4(void)

{

    HANDLE hEvent2;

 

      hEvent2 = CreateEvent(NULL,TRUE,TRUE,NULL);

}

