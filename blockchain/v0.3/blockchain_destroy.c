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
	if (!blockchain)
		return;
	llist_destroy(blockchain->chain, 1, (void (*)(llist_node_t))block_destroy);
	llist_destroy(blockchain->unspent, 1, free);
	free(blockchain);
}
