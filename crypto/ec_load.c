#include "hblk_crypto.h"
/**
 * ec_load - function load public key and privite key from file
 * @folder: the path where files are saved
 * Return: the EC_KEY contaning the public key and privite key
*/
EC_KEY *ec_load(char const *folder)
{
	EC_KEY *mykey = NULL;
	char myfile[512] = {0};
	FILE *pfile;
	struct stat st;

	if (!folder)
		return (NULL);
	if (stat(folder, &st) == -1)
		return (NULL);
	sprintf(myfile, "./%s/%s", folder, PUB_FILENAME);
	pfile = fopen(myfile, "r");
	if (!pfile)
		return (NULL);
	if (!PEM_read_EC_PUBKEY(pfile, &mykey, NULL, NULL))
		return (NULL);
	fclose(pfile);
	sprintf(myfile, "./%s/%s", folder, PRI_FILENAME);
	pfile = fopen(myfile, "r");
	if (!pfile)
		return (NULL);
	if (!PEM_read_ECPrivateKey(pfile, &mykey, NULL, NULL))
		return (NULL);
	fclose(pfile);
	return (mykey);
}
