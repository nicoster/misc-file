#include <tchar.h>
#include <iostream.h>
#include "deelx.h"

char buf[100];
void substr(char*str, int s, int e)
{
	strncpy(buf, str + s, e - s);
	buf[e - s] = 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CRegexpT<char> reg("[+-]?\\d+(\\.\\d+)?");
	char* str = 
	"#1:10"
//	"a+12.223s1d13.52.3a"
//	"0001000200000000"
	;
	int s = 0, e = 0;
	while(e>=0)
	{
		MatchResult ret = reg.Match(str, e);
		s = ret.GetStart();
		e = ret.GetEnd();
		substr(str, s, e);
		cout<<ret.IsMatched()<<")"<<s<<","<<e<<"["<<ret.GetGroupStart(1)<<endl<<buf<<endl;
	}
    return 0;
}






