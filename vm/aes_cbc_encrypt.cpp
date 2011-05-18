/*
* This is an example for openssl aes_cbc_encrypt() encrypt & decrypt a disk file
* With one byte padding at then end of encrypted file
* x --> x_openssl_aes_en --> x_openssl_aes_en_and_de
*
* compile gcc -g -o d d.c /usr/lib/libcrypto.a
*
* author: max.yang
* mail:jianguoyang168 at hotmail dot com
* 2009/04/16
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
//#include <unistd.h>
#include <openssl/aes.h>

int main(int argc, char ** argv)
{
    unsigned char key16[] = "0123456789abcdef";
//salt
    unsigned char iv[16] = {1};
    AES_KEY key;
    int i;
    int ret;

    int fd;
    int fd_en;
    int fd_de;

    int len;
    char * en_name;

    unsigned char in[256] = {0x0};
    unsigned char out[257] = {0x0};

    if (argc != 2)
    {
        printf("Usage %s : filename\n", argv[0]);
    }

    fd = open(argv[1], O_RDONLY);

    if (fd <= 0)
    {
        strerror(errno);
        exit(0);
    }
    en_name = (char *) malloc(strlen(argv[1]) + 40);
    strcpy(en_name, argv[1]);
    strcat(en_name, "_openssl_aes_en");
    fd_en = open(en_name, O_CREAT | O_RDWR);
    if (fd_en <= 0)
    {
        strerror(errno);
        exit(0);
    }

    printf("\n>>AES encryption...\n");
    ret = AES_set_encrypt_key((const unsigned char *)key16, 128, &key);
    if (ret < 0 )
    {
        printf("L%d: AES_set_encrypt_key error!\n", __LINE__);
        return -1;
    }
    memset(iv, 0x0, 16);
    while ( (len = read(fd, in, 256)) == 256)
    {
        AES_cbc_encrypt(in, out, len, &key, iv, AES_ENCRYPT);
        len = write(fd_en, out, len);
        if (len < 0)
        {
            strerror(errno);
            exit(0);
        }
    }

    if (len)
    {
        //BLOCKSIZE == 16
        AES_cbc_encrypt(in, out, len, &key, iv, AES_ENCRYPT);
        ret = len;
        len = (len & 0xFFFFFFF0) + ((len & 0x0F) ? 16 : 0);
        *(out + len) = (len - ret);
        len = write(fd_en, out, len + 1);
        if (len < 0)
        {
            strerror(errno);
            exit(0);
        }
    }

    printf("\nafter en iv:");

    for (i =0; i < 16; ++i)
        printf("%02x", iv[i]);

    close(fd_en);
//-----------------------------------------------------------------------
    fd_en = open(en_name, O_CREAT | O_RDWR);

    if (fd_en <= 0)
    {
        strerror(errno);
        exit(0);
    }

    strcat(en_name, "_and_de");

    fd_de = open(en_name, O_CREAT | O_RDWR);
    if (fd_de <= 0)
    {
        strerror(errno);
        exit(0);
    }
//----------------------------------------------------------------------

    ret = AES_set_decrypt_key((const unsigned char *)key16, 128, &key);
    if (ret < 0 )
    {
        printf("L%d: AES_set_encrypt_key error!\n", __LINE__);
        return -1;
    }

    printf("\n>>AES dencryption...\n");
    memset(iv, 0x0, 16);
    /*   iv[0] = 1; */
    len = read(fd_en, in, 256);
    while ( len == 256)
    {
        AES_cbc_encrypt(in, out, len, &key, iv, AES_DECRYPT);
        ret = read(fd_en, in, 256);
        if (ret == 1)
            len -= (unsigned char) (in[len]);

        len = write(fd_de, out, len);
        if (len < 0)
        {
            strerror(errno);
            exit(0);
        }
        len = ret;
    }
    if (len > 1)
    {
        AES_cbc_encrypt(in, out, len , &key, iv, AES_DECRYPT);
        len -= (unsigned char)(in[len - 1]);
        len -= 1;
        len = write(fd_de, out, len);
        if (len < 0)
        {
            strerror(errno);
            exit(0);
        }
    }

    printf("\nafter de iv:");

    for (i =0; i < 16; ++i)
        printf("%02x", iv[i]);

    close(fd);
    close(fd_en);
    close(fd_de);
    return 1;
}