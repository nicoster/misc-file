#include "common.h"

#define para {L"1", L"2", L"3", L"4"}
void main()
{
	wchar_t* strs[] = (para);
	cout << sizeof(strs) / sizeof(strs[0]);
}