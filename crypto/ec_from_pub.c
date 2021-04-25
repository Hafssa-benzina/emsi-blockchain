#include "hblk_crypto.h"

/**
 * ec_from_pub - a function that creates an EC_KEY structure given a public key
 * @pub: the public key to be converted
 *
 * Return: a pointer to the created EC_KEY structure, or NULL upon failure
 */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_POINT *pub_key;
	EC_GROUP *group;
	EC_KEY *ec_key;

	if (pub == NULL)
		return (NULL);
	ec_key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (ec_key == NULL)
		return (NULL);
	group = (EC_GROUP *)EC_KEY_get0_group(ec_key);
	pub_key = EC_POINT_new(group);
	if (pub_key == NULL)
	{
		EC_KEY_free(ec_key);
		return (NULL);
	}
	if (!EC_POINT_oct2point(group, pub_key, pub, EC_PUB_LEN, NULL))
	{
		EC_KEY_free(ec_key);
		EC_POINT_free(pub_key);
	}
	if (!EC_KEY_set_public_key(ec_key, pub_key))
	{
		EC_KEY_free(ec_key);
		EC_POINT_free(pub_key);
	}

	EC_POINT_free(pub_key);
	return (ec_key);
}
