int main(){}

void foo_int_no_ret(int){}
int foo_int(int){return 0;}
int __cdecl cdecl_foo_int(int){return 0;}
extern "C" int __cdecl C_cdecl_foo_int(int){return 0;}

int pascal stdcall_foo_int(int){return 0;}
extern "C" int __stdcall C_stdcall_foo_int(int){return 0;}


/*
?foo_int_no_ret@@YAXH@Z
?foo_int@@YAHH@Z       
?cdecl_foo_int@@YAHH@Z 
_C_cdecl_foo_int       
?stdcall_foo_int@@YGHH@Z
_C_stdcall_foo_int@4    
*/