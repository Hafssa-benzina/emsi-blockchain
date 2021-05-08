#include "transaction.h"

/**
 * tx_in_create - allocate and initialize a transaction input structure
 * @unspent: points to the unspent transaction output
 * to be converted to a transaction input
 *
 * The created transaction input’s signature structure must be zeroed
 * Return: pointer to the created tx_in, or NULL upon failure
 */
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *tx_in = calloc(1, sizeof(*tx_in));

	if (tx_in == NULL || !unspent)
		return (NULL);
	memcpy(tx_in->block_hash, unspent->block_hash,
	       sizeof(tx_in->block_hash));
	memcpy(tx_in->tx_id, unspent->tx_id, sizeof(unspent->tx_id));
	memcpy(tx_in->tx_out_hash, unspent->out.hash, sizeof(tx_in->tx_out_hash));
	return (tx_in);
}
