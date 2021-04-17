#include "blockchain.h"

/**
 * block_create - create a Block structure and initializes it
 */
block_t *block_create(block_t const *prev, int8_t const *data,
		      uint32_t data_len)
{
	block_t *block;

	b = calloc(1, sizeof(*block));
	if (block == NULL)
		return (NULL);

	block->info.index = prev->info.index + 1;
	block->info.difficulty = 0;
	block->info.timestamp = time(NULL);
	block->info.nonce = 0;
	memcpy(block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	memcpy(block->data.buffer, data, data_len);
	block->data.len = data_len;
	memset(block->hash, 0, SHA256_DIGEST_LENGTH);
	return (block);
}
