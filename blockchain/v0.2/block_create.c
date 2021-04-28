#include "blockchain.h"

/**
 * block_create - create a Block structure and initializes it
 * @prev: a pointer to the previous Block in the Blockchain
 * @data: points to a memory area to duplicate in the Block’s data
 * @data_len: the number of bytes to duplicate in data
 * If data_len is bigger than BLOCKCHAIN_DATA_MAX
 * then only BLOCKCHAIN_DATA_MAX bytes must be duplicated
 *
 * Return: a pointer to an EC_KEY structure or NULL upon failure
 */
block_t *block_create(block_t const *prev, int8_t const *data,
		      uint32_t data_len)
{
	block_t *b;

	b = calloc(1, sizeof(*b));
	if (b == NULL)
		return (NULL);

	b->info.index = prev->info.index + 1;
	b->info.difficulty = 0;
	b->info.timestamp = time(NULL);
	b->info.nonce = 0;
	memcpy(b->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	memcpy(b->data.buffer, data, data_len);
	b->data.len = data_len;
	memset(b->hash, 0, SHA256_DIGEST_LENGTH);
	return (b);
}
