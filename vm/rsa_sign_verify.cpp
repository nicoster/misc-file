// demo how to sign a piece of data
// by Linden 23:49 2003-4-23

#include <openssl/md5.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

main()
{
    #define RSA_KEY_FILE "rsakey.txt"
        // > openssl genrsa -out rsakey.txt 1024
    RSA* key;
    char msg[]="i, i have no data to sign";
    unsigned char md[16];    // md5's len
    unsigned char sig[128]; // 1024/8
    int siglen = sizeof(sig);

    int r;
    
    //SSL_library_init();
    //SSL_load_error_strings();
    //OpenSSL_add_all_algorithms();

    key = RSA_new();

#if 1    // gen 
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

//int RSA_sign(int type, const unsigned char *m, unsigned int m_length,
//    unsigned char *sigret, unsigned int *siglen, RSA *rsa);
    MD5(msg, strlen(msg), md);
    r = RSA_sign(NID_md5, md, sizeof(md), sig, &siglen, key);
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
