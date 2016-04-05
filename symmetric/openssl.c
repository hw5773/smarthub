#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <openssl/conf.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "test.h"

int 	seed_prng(int);
void 	select_random_key(unsigned char *, int);
void 	select_random_iv(unsigned char *, int);
int	encrypt(EVP_CIPHER_CTX *, unsigned char *, int, unsigned char *);
int	decrypt(EVP_CIPHER_CTX *, unsigned char *, int, unsigned char *);
int 	crypto_init(EVP_CIPHER_CTX **, EVP_CIPHER_CTX **, int, int, int, unsigned char *, unsigned char *);
void	handle_errors();

unsigned long get_micro_seconds();

int main (void)
{
	unsigned char 	key[EVP_MAX_KEY_LENGTH];
	unsigned char 	iv[EVP_MAX_IV_LENGTH];

	EVP_CIPHER_CTX	*enc, *dec;

	int decryptedtext_len, ciphertext_len;

	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);

	unsigned long t1 = get_micro_seconds();
	if (!seed_prng(EVP_MAX_KEY_LENGTH))
	{
		printf("Fatal Error! Unable to seed the PRNG!\n");
		abort();
	}
	unsigned long t2 = get_micro_seconds();

	select_random_key(key, EVP_MAX_KEY_LENGTH);

	unsigned long t3 = get_micro_seconds();

	select_random_iv(iv, EVP_MAX_IV_LENGTH);

	unsigned long t4 = get_micro_seconds();

	if (!crypto_init(&enc, &dec, 0, 0, 0, key, iv)) handle_errors();

	unsigned long t5 = get_micro_seconds();

	ciphertext_len = encrypt(enc, plaintext, strlen((char *)plaintext), ciphertext);

	unsigned long t6 = get_micro_seconds();

	printf("Ciphertext is:\n");
	BIO_dump_fp(stdout, (const char *)ciphertext, ciphertext_len);

	unsigned long t7 = get_micro_seconds();

	decryptedtext_len = decrypt(dec, ciphertext, ciphertext_len, decryptedtext);

	unsigned long t8 = get_micro_seconds();

	decryptedtext[decryptedtext_len] = '\0';

	printf("Decrypted text is:\n");
	printf("%s\n", decryptedtext);
	printf("Decrypted text size: %d\n", decryptedtext_len);

	EVP_cleanup();
	ERR_free_strings();

	printf("Plaintext size: %lu\n", strlen(plaintext));
	printf("Ciphertext size: %d\n", ciphertext_len);
	printf("Time for seeding: %lu us\n", t2-t1);
	printf("Time for random key: %lu us\n", t3-t2);
	printf("Time for random iv: %lu us\n", t4-t3);
	printf("Time for Init: %lu us\n", t5-t4);
	printf("Time for Enc: %lu us\n", t6-t5);
	printf("Time for Dec: %lu us\n", t8-t7);

	return 0;
}

void handle_errors(void)
{
	ERR_print_errors_fp(stderr);
	abort();
}

unsigned long get_micro_seconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return 1000000*tv.tv_sec + tv.tv_usec;
}

int seed_prng(int bytes)
{
//	if (!RAND_load_file("/dev/random", bytes))
//		return 0;
	srand(time(NULL));

	return 1;
}

void select_random_key(unsigned char *key, int b)
{
	RAND_bytes(key, b);
}

void select_random_iv(unsigned char *iv, int b)
{
	RAND_pseudo_bytes(iv, b);
}

int crypto_init(EVP_CIPHER_CTX **enc, EVP_CIPHER_CTX **dec, int algorithm, int keysize, int mode
	, unsigned char *key, unsigned char *iv)
{
	if (!(*enc = EVP_CIPHER_CTX_new())) handle_errors();
	if (!(*dec = EVP_CIPHER_CTX_new())) handle_errors();

	if (!(EVP_EncryptInit_ex(*enc, EVP_aes_128_cbc(), NULL, key, iv))) handle_errors();
	if (!(EVP_DecryptInit_ex(*dec, EVP_aes_128_cbc(), NULL, key, iv))) handle_errors();

	return 1;
}

int encrypt(EVP_CIPHER_CTX *ctx, unsigned char *plaintext, int plaintext_len, unsigned char *ciphertext)
{
	int len, ciphertext_len;

	if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) != 1)
		handle_errors();

	ciphertext_len = len;

	if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1)
		handle_errors();

	ciphertext_len += len;

	EVP_CIPHER_CTX_free(ctx);

	return ciphertext_len;
}

int decrypt(EVP_CIPHER_CTX *ctx, unsigned char *ciphertext, int ciphertext_len, unsigned char *plaintext)
{
	int len, plaintext_len;

	if (EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) != 1)
		handle_errors();

	plaintext_len = len;

	if (EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1)
		handle_errors();

	plaintext_len += len;

	EVP_CIPHER_CTX_free(ctx);

	return plaintext_len;
}
