#include "common.h"
#pragma comment(lib, "tricrypto.lib")

int __declspec(dllimport) aes_128_cbc2(int argc, char **argv);

void main()
{
	int3;
	typedef char* LPCHAR;
	char aes_key[] = "83d258caa9b9f98f0a6c8a3766f32d2e"; 
	char aes_iv[] = "11070b131705030d2b251f2f35211d29";	
	LPCHAR argv1[] = 
	{
		"aes-128-cbc", "-in", "d:\\src", "-a", "-K", aes_key, "-iv", aes_iv, "-p",
	};
//	aes_128_cbc2(9, argv1);
	
	LPCHAR argv2[] = 
	{
		"aes-128-cbc", "-d", "-in", "d:\\dst", "-a", "-K", aes_key, "-iv", aes_iv, "-p",

	};
	aes_128_cbc2(10, argv2);
}