#include "crypto.h"
#include "../common/common.h"

int crypto_init(EVP_CIPHER_CTX **enc, EVP_CIPHER_CTX **dec, unsigned char *key, unsigned char *iv)
{
	if (!(*enc = EVP_CIPHER_CTX_new())) handle_errors();
	if (!(*dec = EVP_CIPHER_CTX_new())) handle_errors();

	if (!(EVP_EncryptInit_ex(*enc, EVP_aes_128_gcm(), NULL, key, iv))) handle_errors();
	if (!(EVP_DecryptInit_ex(*dec, EVP_aes_128_gcm(), NULL, key, iv))) handle_errors();

	return 1;
}
