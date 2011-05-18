#define SUPPORT_OPENSSL
#include "common.h"

// #define ENC_FILE "d:\\caroot\\enc.bin"
// #define ENC_FILEW L"d:\\caroot\\enc.bin"
// #define PLAIN_FILE "d:\\caroot\\plain.bin"

#define ENC_FILE "d:\\caroot\\session"
#define ENC_FILEW L"d:\\caroot\\session"
#define PLAIN_FILE "d:\\caroot\\enc2.bin"

int main()
{
	while (1)
	{
		unsigned char iv1[16]=
		{0x12,0x34,0x56,0x78,0x9a,0xbc,0xde,0xf0,
		0x34,0x56,0x78,0x9a,0xbc,0xde,0xf0,0x12};
		unsigned char iv2[16]=
		{0x12,0x34,0x56,0x78,0x9a,0xbc,0xde,0xf0,
		0x34,0x56,0x78,0x9a,0xbc,0xde,0xf0,0x12};
		/*		 
		char* session = "12345678901234567890123456789012";
		/*/
		char* session = "1234567890123456";
		//*/
		_stat results;
		int ret = _wstat(ENC_FILEW, &results);
		CHK_RET(ret == 0, ret);
		int inlen = results.st_size;
		
		char* buf1 = new char[inlen];
		ifstream ifile(ENC_FILE, ios::binary);
		ifile.read(buf1, inlen);
		
		int bitlen = strlen(session) * 8;
		
		AES_KEY aes_ks1;
		AES_set_encrypt_key((const unsigned char*)session, bitlen,&aes_ks1);
		AES_KEY aes_ks2;
		AES_set_decrypt_key((const unsigned char*)session, bitlen,&aes_ks2);
		
		int outlen = (inlen + 15) & 0xfffffff0;
		
		unsigned char* buf2 = (unsigned char*)new char[outlen];
		
		
		AES_cbc_encrypt((const unsigned char*)buf1, (unsigned char*)buf2,
			inlen, &aes_ks1,
			iv1, AES_ENCRYPT);
		
		AES_cbc_encrypt((const unsigned char*)buf2, (unsigned char*)buf1,
			outlen, &aes_ks2,
			iv2, AES_DECRYPT);
	}
		
// 	ofstream f(PLAIN_FILE, ios::binary);
// 	f.write((const char*)buf2, outlen);
// 	f.close();
	return 2;
}