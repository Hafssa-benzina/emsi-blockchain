#include "transaction.h"

/**
 * unspent_tx_out_create - allocate and initialize
 * an unspent transaction output structure
 * @block_hash: the hash of the Block where the referenced transaction output
 * @tx_id: the hash of a transaction where the referenced transaction output
 * @out: points to the referenced transaction output
 *
 * Return: pointer to the created unspent transaction, or NULL upon failure
 */
unspent_tx_out_t *unspent_tx_out_create(
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *out)
{
	unspent_tx_out_t *unspent_tx_out_t = calloc(1, sizeof(*unspent_tx_out_t));

	if (unspent_tx_out_t == NULL)
		return (NULL);
	memcpy(unspent_tx_out_t->block_hash, block_hash,
		sizeof(unspent_tx_out_t->block_hash));
	memcpy(unspent_tx_out_t->tx_id, tx_id, sizeof(unspent_tx_out_t->tx_id));
	memcpy(&unspent_tx_out_t->out, out, sizeof(unspent_tx_out_t->out));
	return (unspent_tx_out_t);
}
