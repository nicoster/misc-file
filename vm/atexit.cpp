#include <cstdlib> 
#include <cstdio>
void Bar() 
{ 
	printf("in bar\n");
} 
void Foo() 
{ 
   atexit(Bar); 
	printf("in foo\n");

} 
void  main() 
{ 
   atexit(Foo); 
} 