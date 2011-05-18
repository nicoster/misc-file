#include <windows.h>
struct raw_mem
{
	BYTE const*pBuf_;
	DWORD dwLen_;
	raw_mem(BYTE const*pBuf = 0, DWORD dwLen = 0) : pBuf_(pBuf), dwLen_(dwLen){}
	size_t operator sizeof(){return dwLen_;}
};

void main()
{
	raw_mem mem("12345", 6);
}