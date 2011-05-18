/*
 *  aes_enc.cpp
 *  TestOpenssl
 *
 *  Created by William Hua on 1/20/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>
#include <string.h>
#include <fstream>
using namespace std;
#include <openssl/aes.h>
#define ENC_BLOCK_SIZE 512
#define OUT_FILE "d:\\caroot\\enc.bin"
#define OUT_FILEW L"d:\\caroot\\enc.bin"
#pragma comment(lib, "libeay32.lib")   
#pragma comment(lib, "ssleay32.lib") 

int main()
{
    _asm int 3;
    bool enc = false;
    unsigned char key16[] = "1234567890123456";
    int key_len = strlen((const char*)key16) * 8;
    unsigned char tmp_buf[ENC_BLOCK_SIZE] = {0};
    //salt
    unsigned char iv[16] = {1};
    
    _stat results;
    if (_wstat(OUT_FILEW, &results) != 0) return 1;
    int in_len = results.st_size;
    
    unsigned char* in_buf = (unsigned char*)new char[in_len];
    ifstream ifile(OUT_FILE, ios::binary);
    ifile.read((char*)in_buf, in_len);
    ifile.close();

    // unsigned char in_buf[] = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\ntestasdfffffeeeeeeeeee\nwwwwwds\n";
    //~ int in_len = strlen((const char*)in_buf);
    
    int out_len = enc ? (in_len & 0xfffffff0) + 16 : in_len;
    unsigned char* out_buf = (unsigned char*)new char[out_len];
    
    AES_KEY key;
    int ret = (enc ? AES_set_encrypt_key : AES_set_decrypt_key)((const unsigned char *)key16, key_len, &key);
    if (ret < 0 )
    {
        printf("L%d: AES_set_en/decrypt_key error!\n", __LINE__);
        return -1;
    }
    
    int buf_ptr = 0;
    while (in_len - buf_ptr >= ENC_BLOCK_SIZE) {
        AES_cbc_encrypt(in_buf + buf_ptr, out_buf + buf_ptr, ENC_BLOCK_SIZE, &key, iv, enc ? AES_ENCRYPT : AES_DECRYPT);
        buf_ptr += ENC_BLOCK_SIZE;
    }
    
    if (enc) {
        // padding
        memcpy(tmp_buf, in_buf + buf_ptr, in_len - buf_ptr);
        memset(tmp_buf + in_len - buf_ptr, out_len - in_len, out_len - in_len);
        AES_cbc_encrypt(tmp_buf, out_buf + buf_ptr, out_len - buf_ptr, &key, iv, AES_ENCRYPT);
    }
    else {
        if (in_len - buf_ptr)
            AES_cbc_encrypt(in_buf + buf_ptr, out_buf + buf_ptr, in_len - buf_ptr, &key, iv, AES_DECRYPT);
        
        // check and remove padding
        unsigned char padding = out_buf[out_len - 1];
        if (padding <= 16)
        {
            int i = out_len;
            for (; out_len - i < padding; i --) {
                if (out_buf[i - 1] != padding) break;
				out_buf[i - 1] = 0;
            }
            
            if (out_len - i >= padding)
                out_len -= padding;
        }
    }
	ofstream f("d:\\caroot\\plain.txt", ios::binary);
	f.write((const char*)out_buf, out_len);
    delete [] out_buf;
	f.close();
    return 0;
}