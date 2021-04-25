#include "hblk_crypto.h"

/**
 * ec_to_pub - a function that extracts the public key
 * from an EC_KEY opaque structure
 * @key: a pointer to the EC_KEY structure to retrieve the public key from
 * @pub: the address at which to store the extracted public key
 * containing both the public and private keys
 * or NULL upon failure
 *
 * Return: a pointer to pub or NULL upon failure
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_POINT *pub_key;
	const EC_GROUP *group;

	if (key == NULL || pub == NULL)
		return (NULL);
	pub_key = EC_KEY_get0_public_key(key);
	group = EC_KEY_get0_group(key);
	if (!EC_POINT_point2oct(group, pub_key, POINT_CONVERSION_UNCOMPRESSED,
				pub, EC_PUB_LEN, NULL))
		return (NULL);
	return (pub);
}
