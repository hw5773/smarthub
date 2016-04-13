#include "crypto.h"
#include "../common/common.h"

int crypto_init(EVP_CIPHER_CTX **enc, EVP_CIPHER_CTX **dec, unsigned char *key, unsigned char *iv)
{
	if (!(*enc = EVP_CIPHER_CTX_new())) handle_errors();
	if (!(*dec = EVP_CIPHER_CTX_new())) handle_errors();

	if (!(EVP_EncryptInit_ex(*enc, EVP_bf_cbc(), NULL, key, iv))) handle_errors();
	if (!(EVP_DecryptInit_ex(*dec, EVP_bf_cbc(), NULL, key, iv))) handle_errors();

   // Setting the key length in the cipher context.
   EVP_CIPHER_CTX_set_key_length(*enc, 24);
   EVP_CIPHER_CTX_set_key_length(*dec, 24);

	return 1;
}
