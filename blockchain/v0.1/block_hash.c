#include "blockchain.h"

/**
 * block_hash - a function that computes the hash of a Block
 * Return: a pointer to hash_buf
 */
uint8_t *block_hash(block_t const *block, uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	sha256((int8_t const *)&(block->info), 4 + 4 + 8 + 8 + 32 + block->data.len, hash_buf);
	return (hash_buf);
}
