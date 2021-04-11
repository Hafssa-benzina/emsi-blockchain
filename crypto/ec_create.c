#include "hblk_crypto.h"

/**
 * A function that creates a new EC key pair
 *
 * Return: a pointer to creat an EC_KEY structure
 */
EC_KEY *ec_create(void)
{
	EC_KEY *ec_key= EC_KEY_new_by_curve_name(EC_CURVE);
	if (ec_key==NULL)
		return (NULL);
	if (!EC_KEY_generate_key(ec_key))
  {
		EC_KEY_free(ec_key);
		return (NULL);
	}
	return (ec_key);
}
