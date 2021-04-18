#include "blockchain.h"

/**
 * blockchain_destroy - a function that deletes an existing Blockchain
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	llist_destroy(blockchain->chain, 1, (void (*)(llist_node_t))block_destroy);
	free(blockchain);
}
