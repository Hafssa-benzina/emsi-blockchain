#include "blockchain.h"

/**
 * block_destroy - frees a block
 * @block: pointer to block to free
 * Void
 */
void block_destroy(block_t *block)
{
	free(block);
}
