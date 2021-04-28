#include "blockchain.h"

/**
 * blockchain_difficulty - a function that computes the difficulty to assign
 * to a potential next Block in the Blockchain
 * @blockchain: blockchain points to the Blockchain to analyze
 *
 * Return: the difficulty to be assigned to a potential next Block
 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *block, *lblock;
	uint64_t eTime, aTime;

	if (!blockchain)
		return (0);
	block = llist_get_tail(blockchain->chain);
	if (!block)
		return (0);
	if (block->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL == 0 &&
	    block->info.index != 0)
	{

		lblock = (block_t *)llist_get_node_at(blockchain->chain,
						       llist_size(blockchain->chain) -
							   DIFFICULTY_ADJUSTMENT_INTERVAL + 1);
		eTime = DIFFICULTY_ADJUSTMENT_INTERVAL * BLOCK_GENERATION_INTERVAL;
		aTime = block->info.timestamp - lblock->info.timestamp;
		if (aTime < eTime / 2)
			return (block->info.difficulty + 1);
		if (aTime > eTime * 2)
			return (block->info.difficulty - 1);
		return (block->info.difficulty);
	}
	else
		return (block->info.difficulty);
}
