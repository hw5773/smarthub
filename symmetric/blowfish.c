#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

int seed_prng(int);
void select_random_key(char *, int);
void select_random_iv(char *, int);
int setup_for_encryption(void);
void select_for_decryption(char *, char *);
char *encrypt_example(EVP_CIPHER_CTX *, char *, int, int *);
char *decrypt_example(EVP_CIPHER_CTX *, char *, int);
unsigned long get_micro_seconds();

int main(int argc, char *argv[])
{
	EVP_CIPHER_CTX	ctx;
	char			key[EVP_MAX_KEY_LENGTH];
	char			iv[EVP_MAX_IV_LENGTH];
	char			*ct, *out;
	char			final[EVP_MAX_BLOCK_LENGTH];
	char			str[] = "123456789abcdef123456789abcdef";
	int				i;

	if (!seed_prng(EVP_MAX_KEY_LENGTH))
	{
		printf("Fatal Error! Unable to seed the PRNG!\n");
		abort();
	}

	printf("EVP_MAX_KEY_LENGTH: %d\n", EVP_MAX_KEY_LENGTH);
	printf("EVP_MAX_IV_LENGTH: %d\n", EVP_MAX_IV_LENGTH);

	select_random_key(key, EVP_MAX_KEY_LENGTH);
	select_random_iv(iv, EVP_MAX_IV_LENGTH);
	
	EVP_EncryptInit(&ctx, EVP_bf_cbc(), key, iv);
	unsigned long before = get_micro_seconds();
	ct = encrypt_example(&ctx, str, strlen(str), &i);
	unsigned long after = get_micro_seconds();
	printf("Ciphertext is %d bytes.\n", i);
	printf("Elapsed Time for Enc: %lu us\n", (after-before));

	EVP_DecryptInit(&ctx, EVP_bf_cbc(), key, iv);
	before = get_micro_seconds();
	out = decrypt_example(&ctx, ct, i);
//	printf("Decrypted: >> %s <<\n", out);
	if (!EVP_DecryptFinal(&ctx, final, &i))
	{
		printf("Padding incorrect.\n");
		abort();
	}
	after = get_micro_seconds();
	final[i] = 0;
	printf("Decrypted: >> %s <<\n", final);
	printf("Elapsed Time for Dec: %lu us\n", (after-before));

	return 0;
}

unsigned long get_micro_seconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	
	return 1000000*tv.tv_sec + tv.tv_usec;
}

int seed_prng(int bytes)
{
	if (!RAND_load_file("/dev/random", bytes))
		return 0;
	return 1;
}

void select_random_key(char *key, int b)
{
	int i;

	RAND_bytes(key, b);
	for (i=0; i<b-1; i++)
		printf("%02X:", key[i]);
	printf("%02X\n", key[b-1]);
}

void select_random_iv(char *iv, int b)
{
	RAND_pseudo_bytes(iv, b);
}

char *encrypt_example(EVP_CIPHER_CTX *ctx, char *data, int inl, int *rb)
{
	char *ret;
	int i, tmp, ol;

	ol = 0;
	ret = (char *)malloc(inl + EVP_CIPHER_CTX_block_size(ctx));

	for (i = 0; i < inl /16; i++)
	{
		EVP_EncryptUpdate(ctx, &ret[ol], &tmp, &data[ol], 16);
		ol += tmp;
	}

	if (inl % 8)
	{
		EVP_EncryptUpdate(ctx, &ret[ol], &tmp, &data[ol], inl % 16);
		ol += tmp;
	}

	EVP_EncryptFinal(ctx, &ret[ol], &tmp);
	*rb = ol + tmp;
	return ret;
}

char *decrypt_example(EVP_CIPHER_CTX *ctx, char *ct, int inl)
{
	char *pt = (char *)malloc(inl + EVP_CIPHER_CTX_block_size(ctx) + 1);
	int ol;

	EVP_DecryptUpdate(ctx, pt, &ol, ct, inl);

	if (!ol)
	{
		free(pt);
		return NULL;
	}
	pt[ol] = 0;
	return pt;
}
