#include "hblk_crypto.h"

/**
 * ec_save - a function that saves an existing EC key pair on the disk
 * @key: points to the EC key pair to be saved on disk
 * @folder: the path to the folder in which to save the keys
 *
 * Return: 1 or 0 upon success or failure
 */
int ec_save(EC_KEY *key, char const *folder)
{
	FILE *fp;
	char path[128] = {0};

	if (!key || !folder)
		return (0);
	mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	sprintf(path, "%s/" PRV_FILE, folder);
	fp = fopen(path, "w");
	if (!fp)
		return (0);
	if (!PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL))
	{
		/*fclose(fp);*/
		/*return (0);*/
	}
	fclose(fp);
	sprintf(path, "%s/" PUB_FILE, folder);
	fp = fopen(path, "w");
	if (!fp)
		return (0);
	if (!PEM_write_EC_PUBKEY(fp, key))
	{
		fclose(fp);
		return (0);
	}
	fclose(fp);
	return (1);
}
