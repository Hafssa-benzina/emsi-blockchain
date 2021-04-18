#include "blockchain.h"

/**
 * A function that deletes an existing block
 */
void block_destroy(block_t *block);
{
	free(block);
}
