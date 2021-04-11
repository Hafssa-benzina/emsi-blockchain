#include "hblk_crypto.h"

/**
 *A function that computes the hash of a sequence of bytes
 *s is the sequence of bytes to be hashed
 *len is the number of bytes to hash in s
 */
uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH])
{
  	if (digest != NULL){
		digest = SHA256((const unsigned char *)s, len, digest);
		return digest;
	}
  	else
   		 return NULL;
}
