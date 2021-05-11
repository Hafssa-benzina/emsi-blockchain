#include "hblk_crypto.h"
/**
 * ec_save - function save public key and privite key in file
 * @key: the EC_KEY contaning the public and privite key
 * @folder: the path where key's files are saved
 * Return: 1 or 0 upon success or failure
*/
int ec_save(EC_KEY *key, char const *folder)
{
	char my_file[BUFSIZ];
	FILE *pfile;

	if (!key || !folder)
		return (0);
	mkdir(folder, 0700);
	sprintf(my_file, "%s/%s", folder, PRI_FILENAME);
	pfile = fopen(my_file, "w");
	if (!pfile)
		return (0);
	if (!PEM_write_ECPrivateKey(pfile, key, NULL, NULL, 0, NULL, NULL))
	{
		fclose(pfile);
		return (0);
	}
	fclose(pfile);
	sprintf(my_file, "%s/%s", folder, PUB_FILENAME);
	pfile = fopen(my_file, "w");
	if (!pfile)
		return (0);
	if (!PEM_write_EC_PUBKEY(pfile, key))
	{
		fclose(pfile);
		return (0);
	}
	fclose(pfile);
	return (1);
}
