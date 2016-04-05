#include <wolfssl/wolfcrypt/rsa.h>
#include <stdio.h>
#include <string.h>
#include "../common/test.h"

#define KEYSIZE 	1024
#define FOURK_BUF 	4096

int handle_errors();

int main(void)
{
	RsaKey 			pub, priv;
	RNG				rng;
//	int				size = (int)strlen(plaintext), der_size, idx;
	long			e = 65537;
	unsigned char	der[4096];

	if (!(wc_InitRng(&rng)))
	{
		printf("Error in Init for the rng\n");
	}

	if (!(wc_InitRsaKey(&pub, 0)))
	{
		printf("Error in Init for the pub\n");
	}

	if (!(wc_InitRsaKey(&priv, 0)))
	{
		printf("Error in Init for the priv\n");
	}

	if (!(wc_MakeRsaKey(&priv, KEYSIZE, e, &rng)))
	{
		printf("Error in generating the rsa key\n");
	}

	if (!(wc_RsaKeyToDer(&priv, der, FOURK_BUF)))
	{
		printf("Error in ToDer\n");
	}

	printf("privkey: %s\n", der);

/*
	if (!(wc_RsaPublicEncrypt(plaintext, size, ciphertext, size, &pub, &rng)))
	{
		printf("Failed in encrypting\n");
	}
*/
	if (!(wc_FreeRsaKey(&pub)))
	{
		printf("Failed Free in enc\n");
	}

	if (!(wc_FreeRsaKey(&priv)))
	{
		printf("Failed Free in dec\n");
	}

//	free(der_cert);
//	free(privkey);

	return 0;
}


