 #include <openssl/evp.h>
 #include <openssl/rsa.h>
 #include <openssl/engine.h>

int main(void)
{
	EVP_PKEY_CTX *ctx;
	ENGINE *eng = NULL;
 	unsigned char *out, *in = "123456789\t";
 	size_t outlen, inlen = 10; 
 	EVP_PKEY *key;
 /* NB: assumes eng, key, in, inlen are already set up,
  * and that key is an RSA public key
  */
 	ctx = EVP_PKEY_CTX_new(key,eng);
 	if (!ctx)
        /* Error occurred */
 	if (EVP_PKEY_encrypt_init(ctx) <= 0)
        /* Error */
 	if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_OAEP_PADDING) <= 0)
        /* Error */

 /* Determine buffer length */
 	if (EVP_PKEY_encrypt(ctx, NULL, &outlen, in, inlen) <= 0)
        /* Error */

 	out = OPENSSL_malloc(outlen);

 	if (!out)
        /* malloc failure */
 
 	if (EVP_PKEY_encrypt(ctx, out, &outlen, in, inlen) <= 0)
        /* Error */

 /* Encrypted data is outlen bytes written to buffer out */

	return 1;
}
