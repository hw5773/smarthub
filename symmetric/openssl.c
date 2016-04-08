#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "text.h"
#include "crypto.h"
#include "../common/common.h"

void 	select_random_key(unsigned char *, int);
void 	select_random_iv(unsigned char *, int);
int		encrypt(EVP_CIPHER_CTX *, unsigned char *, int, unsigned char *);
int		decrypt(EVP_CIPHER_CTX *, unsigned char *, int, unsigned char *);

int main (int argc, char *argv[])
{
   if (argc != 3)
   {
      printf("Usage: ./<executable> <num of crypt> <serial number>\n");
      exit(-1);
   }

	FILE *out;
	float			   num_of_crypt = atof(argv[1]);
	unsigned char 	key[EVP_MAX_KEY_LENGTH];
	unsigned char 	iv[EVP_MAX_IV_LENGTH];
	char	         *fname;

	EVP_CIPHER_CTX	*enc, *dec;

	int i, decryptedtext_len, ciphertext_len;

	asprintf(&fname, "%s_%d_%s.log", argv[0], (int)num_of_crypt, argv[2]);
	
	out = fopen((const char *)fname, "w");

	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);

	double t1 = get_micro_seconds();
	if (!seed_prng(EVP_MAX_KEY_LENGTH))
	{
		printf("Fatal Error! Unable to seed the PRNG!\n");
		abort();
	}
	double t2 = get_micro_seconds();

	select_random_key(key, EVP_MAX_KEY_LENGTH);

	double t3 = get_micro_seconds();

	select_random_iv(iv, EVP_MAX_IV_LENGTH);

	double t4 = get_micro_seconds();

	if (!crypto_init(&enc, &dec, key, iv)) handle_errors();

	double t5 = get_micro_seconds();

	for (i=0; i<num_of_crypt; i++)
		ciphertext_len = encrypt(enc, (unsigned char *)plaintext, 1000, ciphertext);

	double t6 = get_micro_seconds();

	double t7 = get_micro_seconds();

	for (i=0; i<num_of_crypt; i++)
		decryptedtext_len = decrypt(dec, ciphertext, ciphertext_len, decryptedtext);

	double t8 = get_micro_seconds();

	decryptedtext[decryptedtext_len] = '\0';

	printf("Decrypted text size: %d\n", decryptedtext_len);

	EVP_cleanup();
	ERR_free_strings();

	printf("Plaintext size: %d\n", (int)strlen(plaintext));
	printf("Ciphertext size: %d\n", ciphertext_len);
	printf("The number of crypt: %d\n", (int)num_of_crypt);
	printf("Time for seeding: %.6lf us\n", (t2-t1)*1000000);
	printf("Time for random key: %.6lf us\n", (t3-t2)*1000000);
	printf("Time for random iv: %.6lf us\n", (t4-t3)*1000000);
	printf("Time for Init: %.6lf us\n", (t5-t4)*1000000);
	printf("Time for Enc: %.6lf us\n", (t6-t5)*1000000);
	printf("Avg Time for Enc: %f us\n", (t6-t5)*1000000/num_of_crypt);
	printf("Time for Dec: %.6lf us\n", (t8-t7)*1000000);
	printf("Avg Time for Dec: %f us\n", (t8-t7)*1000000/num_of_crypt);

	print_log(out, "Before encryption", t5);
	print_log(out, "After encryption", t6);
	print_log(out, "Before decryption", t7);
	print_log(out, "After decryption", t8);

	fclose(out);

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
