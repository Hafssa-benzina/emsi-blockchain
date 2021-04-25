#include "hblk_crypto.h"

/**
 * ec_create - a function that creates a new EC key pair
 * return a pointer to an EC_KEY structure
 * containing both the public and private keys
 * or NULL upon failure
 *
 * Return: a pointer to an EC_KEY structure or NULL upon failure
 */
EC_KEY *ec_create(void)
{
	/* EC_CURVE == secp256k1 */
	EC_KEY *ec_key = EC_KEY_new_by_curve_name(EC_CURVE);

	if (ec_key == NULL)
		return (NULL);
	if (!EC_KEY_generate_key(ec_key))
	{
		EC_KEY_free(ec_key);
		return (NULL);
	}
	return (ec_key);
}
