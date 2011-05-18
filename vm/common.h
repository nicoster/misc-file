#pragma warning(disable:4786)

#define WINVER			0x0500
#define _WIN32_WINNT	0x0500
#define _WIN32_IE		0x0501
#define _RICHEDIT_VER	0x0100

#define WIN32_LEAN_AND_MEAN		
#include <windows.h>
#include <objbase.h>
#include <ocidl.h>
#include <tchar.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <functional>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>

#include <comutil.h>
#include <atlbase.h>
#include <atlconv.h>

#ifdef SUPPORT_OPENSSL
#include <openssl/ssl.h> 
#include <openssl/err.h> 
#include <openssl/bio.h> 
#endif 

#pragma comment(lib, "libeay32.lib")   
#pragma comment(lib, "ssleay32.lib") 

using namespace std;

#define int3 _asm int 3

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))
#endif

#define CHK_RET(b, x) do{if (!(b)) {cerr << x << endl; return 1;}} while (0)
