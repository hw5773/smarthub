#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

int 	crypto_init(EVP_CIPHER_CTX **, EVP_CIPHER_CTX **, unsigned char *, unsigned char *);
