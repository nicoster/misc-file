#include <windows.h>
void main()
{

	union
	{
		WORD w;
		struct bit
		{
			WORD a:1;
			WORD b:1;
			WORD d:1;
			WORD e:1;
			WORD f:1;
			WORD g:1;
			WORD h:1;
			WORD i:1;
			WORD j:1;
			WORD k:1;
			WORD l:1;
			WORD m:1;
			WORD n:1;
			WORD o:1;
			WORD p:1;
			WORD q:1;
		} bits;
	} wTemp;
	wTemp.w = 0x3d24;

}