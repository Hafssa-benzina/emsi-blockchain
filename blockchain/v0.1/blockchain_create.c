#include "blockchain.h"
#define GENESIS_TIMESTAMP 1537578000
#define GENESIS_DATA "Holberton School"
#define GENESIS_DATA_LEN 16
#define GENESIS_HASH "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"

/**
*blockchain_create - Create a blockchain
*The Blockchain must contain one block upon creation.
*This block is called the genesis Block. Its content is static
*Return: blockchain struct
*/
blockchain_t *blockchain_create(void)
{
	blockchain_t *list;
	block_t *genesis;

	list = calloc(1, sizeof(*list));
	if (list == NULL)
		return (NULL);
	genesis = calloc(1, sizeof(*genesis));
	if (genesis == NULL)
	{
		free(list);
		return (NULL);
	}
	list->chain = llist_create(MT_SUPPORT_TRUE);
	if (list->chain == NULL)
	{
		free(list);
		free(genesis);
		return (NULL);
	}
	genesis->info.index = 0;
	genesis->info.difficulty = 0;
	genesis->info.timestamp = GENESIS_TIMESTAMP;
	genesis->info.nonce = 0;
	memset(genesis->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	memcpy(&(genesis->data.buffer), GENESIS_DATA, GENESIS_DATA_LEN);
	genesis->data.len = GENESIS_DATA_LEN;
	memcpy(&(genesis->hash), GENESIS_HASH, SHA256_DIGEST_LENGTH);
	if (llist_add_node(list->chain, genesis, ADD_NODE_FRONT) == -1)
	{
		free(genesis);
		llist_destroy(list->chain, 0, NULL);
		free(list);
		return (NULL);
	}
	return (list);
}
