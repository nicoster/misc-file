#include <iostream>
#include <new>
#include <excpt.h>
#include <malloc.h>
using namespace std;
#define EXCEPTION_STACK_OVERFLOW ((unsigned long)0xC00000FDL)

int main( void )
{
    struct Test
    {
        int i;
        Test()  throw() : i(1) { cout << "construct" << endl; }
        ~Test() throw()        { cout << "destruct"  << endl; }
        void print() throw()   { cout << i << endl; }
    };

    __try
    {
        Test& t1 = *new( _alloca( sizeof(Test) ) ) Test;
        t1.print();
        t1.~Test();
    }
    __except( EXCEPTION_STACK_OVERFLOW==GetExceptionCode() ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH )
    {
        cerr << "alloca fail.\n";
    }

    return 0;
} 