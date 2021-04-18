#include "blockchain.h"

/**
 * A function that deletes an existing Blockchain
 * along with all the Blocks it contains
 * blockchain: point to the Blockchain structure to delete
 */
void block_destroy(block_t *block);
{
	llist_destroy(block_t->chain, 1, (void (*)(llist_node_t))block_destroy);
	free(block_t);
}
