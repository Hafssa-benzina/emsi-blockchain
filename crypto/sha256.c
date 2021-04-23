#include "hblk_crypto.h"
/**
 * sha256 - a function that computes the hash of a sequence of bytes
 * Return: a pointer to digest or NULL if digest happens to be NULL
 */
uint8_t *sha256(int8_t const *s, size_t len, 
		uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (digest == NULL)
		return (NULL);
	digest = SHA256((const unsigned char *)s, len, digest);
	return (digest);
}
