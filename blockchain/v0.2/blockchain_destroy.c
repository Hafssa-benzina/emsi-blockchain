#include "blockchain.h"

/**
 * blockchain_destroy - a function that deletes an existing Blockchain
 * along with all the Blocks it contains
 * @blockchain: point to the Blockchain structure to delete
 *All the Blocks in the chain linked list must be destroyed
 * Void
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	llist_destroy(blockchain->chain, 1, (void (*)(llist_node_t))block_destroy);
	free(blockchain);
}
