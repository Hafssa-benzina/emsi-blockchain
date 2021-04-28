#include "blockchain.h"

int nb_z(uint8_t nb);

/**
 * hash_matches_difficulty - a function that checks
 * whether a given hash matches a given difficulty
 * @hash: the hash to check
 * @difficulty: the minimum difficulty the hash should match
 *
 * Return: return 1 if the difficulty is respected, or 0 otherwise
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			    uint32_t difficulty)
{
	uint32_t i = 0, j = 0, k = 0;

	if (!hash || difficulty > SHA256_DIGEST_LENGTH * 8)
		return (0);
	k = nb_z(hash[i]);
	while (j < difficulty && k != 0)
	{
		j += nb_z(hash[i]);
		i++;
		if (k < 8)
			break;
		k = nb_z(hash[i]);
	}
	if (j >= difficulty)
		return (1);
	else
		return (0);
}

/**
 * nb_z - the number of left zero in a byte
 * @i: the number to test
 *
 * Return: the number or 0 if no zeros
 */
int nb_z(uint8_t i)
{
	if (i == 0)
		return (8);
	if (i == 1)
		return (7);
	if (i <= 3)
		return (6);
	if (i <= 7)
		return (5);
	if (i <= 15)
		return (4);
	if (i <= 31)
		return (3);
	if (i <= 63)
		return (2);
	if (i <= 127)
		return (1);
	return (0);
}
