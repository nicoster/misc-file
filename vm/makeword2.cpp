#include "common.h"

#define MAKEWORD2(short_value, bool_value) (((WORD)short_value & 0x7fff) | ((WORD)bool_value << 15))
#define GETSHORTFROMWORD(word_value) ((WORD)word_value & 0x7fff)
#define GETBOOLFROMWORD(word_value) (!!((WORD)word_value & 0x8000))

template<int first, int second>
struct tagDummy
{
	DWORD b : first;
	DWORD d : second;
};

void main()
{
	tagDummy<1, 2> a;
	WORD w = MAKEWORD2(234, FALSE);
	cout << GETSHORTFROMWORD(w) << " " << GETBOOLFROMWORD(w) << endl;
}