// demo how to sign a piece of data
// by Linden 23:49 2003-4-23

#include "common.h"
#include <openssl/md5.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

main()
{
	int3;
    #define RSA_KEY_FILE "d:\\caroot\\pri.key"
    RSA* key;
    unsigned char msg[]="i, i have no data to sign";
    unsigned char md[16];    // md5's len
    unsigned char sig[128]; // 1024/8
    int siglen = sizeof(sig);

    int r;
    
    //SSL_library_init();
    //SSL_load_error_strings();
    //OpenSSL_add_all_algorithms();

    key = RSA_new();

#if 0    // gen 
    puts("genrsa...(maybe a few seconds)");
    key = RSA_generate_key(1024, 65537, NULL, NULL);
    puts("ok");
#else    // read in
    {    
#if 0 // 曾经ok过吗？忘了
        FILE *fp = fopen(RSA_KEY_FILE, "r");
       key = PEM_read_RSAPrivateKey(fp, &key, NULL, NULL);
#else
        int i;
        EVP_PKEY* k;
        BIO *in = BIO_new(BIO_s_file_internal());
        i = BIO_read_filename(in, RSA_KEY_FILE);
        if (i<=0) puts("read key file err");
        else
            k = PEM_read_bio_PrivateKey(in, NULL, NULL, NULL);    
        key = RSAPrivateKey_dup(k->pkey.rsa);
        EVP_PKEY_free(k);
        BIO_free(in);
#endif
    }
#endif

#if 0    // display. there's err
    {
    //BIO *o = BIO_new_fd(fileno(stdout), BIO_NOCLOSE);
    BIO *o = BIO_new(BIO_s_file());
    RSA_print(o, key, 0);
    BIO_free(o);
    }
#endif

    
 #define BUFLEN 144
	unsigned char   input[BUFLEN] = {1, 2, 3, 4, 5, 6, 7, 8}, 
		output[BUFLEN] = {0}, output1[BUFLEN] = {0}, pkn[BUFLEN] = {0},pkd[BUFLEN] = {0},pkp[BUFLEN] = {0},pkq[BUFLEN] = {0},pku[BUFLEN] = {0},pkdp[BUFLEN] = {0},pkdq[BUFLEN] = {0},pke[BUFLEN] = {0}; 
  	int   len_n = 0, len_e = 0;//, r= 0; 

	len_n   =   BN_bn2bin(key-> n,   pkn); 
 	len_e   =   BN_bn2bin(key-> e,   pke); 
// 	r   =   BN_bn2bin(key-> d,   pkd); 
// 	r   =   BN_bn2bin(key-> dmp1,   pkdp); 
// 	r   =   BN_bn2bin(key-> dmq1,   pkdq); 
// 	r   =   BN_bn2bin(key-> p,   pkp); 
// 	r   =   BN_bn2bin(key-> q,   pkq); 
// 	r   =   BN_bn2bin(key-> iqmp,   pku); 

	//encrypt 

	RSA   *pkey; 
	pkey   =   RSA_new(); 
	pkey-> n   =   BN_new(); 
 	pkey-> e   =   BN_new(); 
// 	pkey-> dmq1   =   BN_new(); 
// 	pkey-> dmp1   =   BN_new(); 
// 	pkey-> p   =   BN_new(); 
// 	pkey-> q   =   BN_new(); 
// 	pkey-> iqmp   =   BN_new(); 
// 	pkey-> d   =   BN_new(); 
// 	BN_bin2bn((unsigned   char   *)pkd,   BUFLEN,   pkey-> d); 
// 	BN_bin2bn((unsigned   char   *)pkdq,   BUFLEN,   pkey-> dmq1); 
// 	BN_bin2bn((unsigned   char   *)pkdp,   BUFLEN,   pkey-> dmp1); 
// 	BN_bin2bn((unsigned   char   *)pkp,   BUFLEN,   pkey-> p); 
// 	BN_bin2bn((unsigned   char   *)pkq,   BUFLEN,   pkey-> q); 
// 	BN_bin2bn((unsigned   char   *)pku,   BUFLEN,   pkey-> iqmp); 
 	BN_bin2bn(pke,   len_e,   pkey-> e); 
	BN_bin2bn(pkn,   len_n,   pkey-> n); 

	len_n   =   BN_bn2bin(key-> n,   pkn); 
 	len_e   =   BN_bn2bin(key-> e,   pke); 

//int RSA_sign(int type, const unsigned char *m, unsigned int m_length,
//    unsigned char *sigret, unsigned int *siglen, RSA *rsa);
  //  MD5(msg, strlen(msg), md);
  //  r = RSA_sign(NID_md5, md, sizeof(md), sig, &siglen, key);
    if (!r)
        puts("error in sign");

#if 0
    sig[0]++; // 假想的错误
#endif

//int RSA_verify(int type, const unsigned char *m, unsigned int m_length,
//    unsigned char *sigbuf, unsigned int siglen, RSA *rsa);
    r = RSA_verify(NID_md5, md, sizeof(md), sig, siglen, key);
    if (!r)
        puts("error in verify");
    puts("is there errs? no? ok!");

    RSA_free(key);

    return 0;
}
