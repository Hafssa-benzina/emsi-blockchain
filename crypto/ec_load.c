#include "hblk_crypto.h"

/**
 * ec_load - a function that loads an EC key pair from the disk
 * @folder: the path to the folder from which to load the keys
 *
 * Return: a pointer to the created EC key pair, or NULL upon failure
 */
EC_KEY *ec_load(char const *folder)
{
	FILE *fp;
	char path[128] = {0};
	EC_KEY *key = NULL;

	if (!folder)
		return (0);

	sprintf(path, "%s/" PUB_FILE, folder);
	fp = fopen(path, "r");
	if (!fp)
	{
		EC_KEY_free(key);
		return (0);
	}
	if (!PEM_read_EC_PUBKEY(fp, &key, NULL, NULL))
	{
		EC_KEY_free(key);
		fclose(fp);
		return (0);
	}
	fclose(fp);

	sprintf(path, "%s/" PRV_FILE, folder);
	fp = fopen(path, "r");
	if (!fp)
		return (0);
	if (!PEM_read_ECPrivateKey(fp, &key, NULL, NULL))
	{
		fclose(fp);
		return (0);
	}
	fclose(fp);
	return (key);
}
