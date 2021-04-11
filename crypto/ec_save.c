#include "hblk_crypto.h"

/**
 *A function that saves an existing EC key pair on the disk
 * @key: points to the EC key pair to be saved on disk
 * @folder: the path to the folder in which to save the keys
 * Return: 1 or 0 upon success or failure
 */
int ec_save(EC_KEY *key, char const *folder)
{
	char buf[BUFSIZ];
	FILE *fp;

	if (!key || !folder || strlen(folder) + strlen(PUB_FILENAME) > BUFSIZ)
		return (0);
	mkdir(folder, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	sprintf(buf, "%s/%s", folder, PUB_FILENAME);
	fp = fopen(buf, "w");
	if (!fp)
		return (0);
	if (!PEM_write_EC_PUBKEY(fp, key))
		goto out;
	fclose(fp);
	sprintf(buf, "%s/%s", folder, PRI_FILENAME);
	fp = fopen(buf, "w");
	if (!fp)
		return (0);
	if (!PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL))
		goto out;
	fclose(fp);
	return (1);
out:
	fclose(fp);
	return (0);
}
