#include "hblk_crypto.h"

/**
 * A function that creates a new EC key pair
 * Return: a pointer to creat an EC_KEY structure
 */
EC_KEY *ec_create(void)
{
	/* EC_CURVE == secp256k1 */
	EC_KEY *key;

	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (!key)
		return (NULL);
	if (!EC_KEY_generate_key(key))
	{
		EC_KEY_free(key);
		return (NULL);
	}
	return (key);
}
