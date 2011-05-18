#include "windows.h"
void main( void )
{
    __try
    {
        //~ try
        //~ {
            //~ // Execute code to accomplish something.
        //~ }
	}
        __except ( EXCEPTION_EXECUTE_HANDLER)
        {
			;
            // This will be executed if the code in the __try block
            // causes an access violation or other hard crash.
            // The code in here is also called the exception handler.
        }
    //~ __finally
    //~ {
        //~ // This will be executed no matter if the function causes a
        //~ //  crash or not.  This is where mandatory cleanup code goes.
    //~ }
}

