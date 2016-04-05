#include <stdio.h>
#include <wolfssl/wolfcrypt/aes.h>
#include "test.h"

int		select_random_key(unsigned char *, int);
int		select_random_iv(unsigned char *, int);

int main(void)
{
	unsigned char	key[17] = "0123456789abcdef";
	unsigned char	iv[17] = "0000000000000000";
	unsigned long	t1, t2, t3, t4, t5, t6;

	struct Aes enc, dec;
	int	size = (int)strlen(plaintext);

	t1 = get_micro_seconds();

	if (!(wc_AesSetKey(&enc, key, AES_BLOCK_SIZE, iv, AES_ENCRYPTION)))
	{
		printf("Failed to set AES key in enc\n");
	}

	t2 = get_micro_seconds();

	if (!(wc_AesSetKey(&dec, key, AES_BLOCK_SIZE, iv, AES_DECRYPTION)))
	{
		printf("Failed to set AES key in dec\n");
	}

	t3 = get_micro_seconds();

	if (!(wc_AesCbcEncrypt(&enc, ciphertext, plaintext, size)))
	{
		printf("Encrypt Failed\n");
	}

	t4 = get_micro_seconds();

	size = (int)strlen(ciphertext);

	t5 = get_micro_seconds();

	if (!(wc_AesCbcDecrypt(&dec, decryptedtext, ciphertext, size)))
	{
		printf("Decrypt Failed\n");
	}

	t6 = get_micro_seconds();

	printf("Plaintext: \n");
	printf("%s\n", plaintext);
	printf("Ciphertext:\n");
	printf("%s\n", ciphertext);
	printf("Decryptedtext:\n");
	printf("%s\n", decryptedtext);
	printf("Elapsed time for set enc: %lu us\n", t2-t1);
	printf("Elapsed time for set dec: %lu us\n", t3-t2);
	printf("Elapsed time for encryption: %lu us\n", t4-t3);
	printf("Elapsed time for decryption: %lu us\n", t6-t5);

	return 0;
}
