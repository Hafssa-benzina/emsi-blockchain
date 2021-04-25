#include "hblk_crypto.h"

/**
 * ec_verify - verifie the signature using a given EC_KEY public key
 * @key: points to the EC_KEY structure containing he public key
 * @msg: points to the msglen characters to be signed
 * @msglen: message length
 * @sig: points to the signature to be checked
 *
 * Return: return 1 if the signature is valid, and 0 otherwise
 */
uint ec_verify(EC_KEY const *key, uint8_t const *msg, size_t msglen,
	       sig_t const *sig)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];

	if (!key || !msg || !sig)
		return (0);
	if (!EC_KEY_check_key(key))
		return (0);
	if (!SHA256(msg, msglen, hash))
		return (0);
	if (!ECDSA_verify(0, hash, SHA256_DIGEST_LENGTH, sig->sig, sig->len,
			  (EC_KEY *)key))
		return (0);
	return (1);
}
