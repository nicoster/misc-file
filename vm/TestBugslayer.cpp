#include "afx.h"
#include "afxcmn.h"
#include "UnhandledExceptionFilter.h"

CUnhandledExceptionFilter();

void foo(int){memset(0, 0, 1);}
void bar(int){foo(3);}
void baz(int){bar(2);}
void main(){baz(1);}