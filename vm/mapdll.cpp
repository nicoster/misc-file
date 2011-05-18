#define MAPAPI _declspec(dllexport)
#include "mapdll.h"
void MAPAPI func(map& m)
{
	map n;
	n = m;
}
void MAPAPI func2(map& m){m = map();}
	
/* 
cl.exe  /nologo  /W3 /Gm /GX /Zi /D /GZ /D "WIN32" /D "_CONSOLE" /D "_MBCS"  /I"D:\Program Files\Microsoft Platform SDK\Include;" /I"D:\Header Collection\SDK2003\include"/I../include /I../../include /I"D:\Header Collection\wtl71\include" /I"d:\nickx\Desktop\zlib123-dll\include" /MTd /Od /D "_DEBUG" /LD mapdll.cpp /link /LIBPATH:D:\Header~1\SDK2003\Lib /LIBPATH:d:\nickx\Desktop\zlib123-dll\lib /subsystem:console /incremental:yes /pdb:mapdll.pdb /debug /machine:I386 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 
*/