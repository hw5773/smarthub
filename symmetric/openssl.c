#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "text.h"
#include "crypto.h"
#include "../common/common.h"

void 	select_random_key(unsigned char *, int);
void 	select_random_iv(unsigned char *, int);
int		encrypt(EVP_CIPHER_CTX *, unsigned char *, int, unsigned char *);
int		decrypt(EVP_CIPHER_CTX *, unsigned char *, int, unsigned char *);

int main (void)
{
	unsigned char 	key[EVP_MAX_KEY_LENGTH];
	unsigned char 	iv[EVP_MAX_IV_LENGTH];

	EVP_CIPHER_CTX	*enc, *dec;

	int i, decryptedtext_len, ciphertext_len;

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

	if (!crypto_init(&enc, &dec, key, iv)) handle_errors();

	unsigned long t5 = get_micro_seconds();

	for (i=0; i<10000; i++)
		ciphertext_len = encrypt(enc, plaintext, 1000, ciphertext);

	unsigned long t6 = get_micro_seconds();

	unsigned long t7 = get_micro_seconds();

	for (i=0; i<10000; i++)
		decryptedtext_len = decrypt(dec, ciphertext, ciphertext_len, decryptedtext);

	unsigned long t8 = get_micro_seconds();

	decryptedtext[decryptedtext_len] = '\0';

	printf("Decrypted text size: %d\n", decryptedtext_len);

	EVP_cleanup();
	ERR_free_strings();

	printf("Plaintext size: %d\n", (int)strlen(plaintext));
	printf("Ciphertext size: %d\n", ciphertext_len);
	printf("Time for seeding: %lu us\n", t2-t1);
	printf("Time for random key: %lu us\n", t3-t2);
	printf("Time for random iv: %lu us\n", t4-t3);
	printf("Time for Init: %lu us\n", t5-t4);
	printf("Time for Enc: %lu us\n", t6-t5);
	printf("Avg Time for Enc: %f us\n", (t6-t5)/10000.0);
	printf("Time for Dec: %lu us\n", t8-t7);
	printf("Avg Time for Dec: %f us\n", (t8-t7)/10000.0);

	return 0;
}

void select_random_key(unsigned char *key, int b)
{
	RAND_bytes(key, b);
}

void select_random_iv(unsigned char *iv, int b)
{
	RAND_pseudo_bytes(iv, b);
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

	return plaintext_len;
}
