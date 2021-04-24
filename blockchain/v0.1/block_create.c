#include "blockchain.h"

/**
 * block_create - create a Block structure and initializes it
 * @prev: a pointer to the previous Block in the Blockchain
 * @data: points to a memory area to duplicate in the Block’s data
 * @data_len: the number of bytes to duplicate in data
 *
 * Return: a pointer to an EC_KEY structure or NULL upon failure
 */
block_t *block_create(block_t const *prev, int8_t const *data,
		      uint32_t data_len)
{
	block_t *blk;

	blk = calloc(1, sizeof(*blk));
	if (blk == NULL)
		return (NULL);

	blk->info.index = prev->info.index + 1;
	blk->info.difficulty = 0;
	blk->info.timestamp = time(NULL);
	blk->info.nonce = 0;
	memcpy(blk->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	memcpy(blk->data.buffer, data, data_len);
	blk->data.len = data_len;
	memset(blk->hash, 0, SHA256_DIGEST_LENGTH);
	return (blk);
}
