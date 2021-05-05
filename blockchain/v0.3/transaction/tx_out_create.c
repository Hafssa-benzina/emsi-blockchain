#include "transaction.h"

/**
 * tx_out_create - allocate and initialize a transaction output structure
 * @amount: the amount of the transaction
 * @pub: the public key of the transaction receiver
 *
 * Return: pointer to the created tx_out, or NULL upon failure
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *tx_out;

	if (amount == 0 || pub == NULL)
		return (NULL);
	tx_out = calloc(1, sizeof(*tx_out));
	if (tx_out == NULL)
		return (NULL);
	tx_out->amount = amount;
	memcpy(tx_out->pub, pub, sizeof(tx_out->pub));
	if (!sha256((int8_t const *)tx_out,
		    sizeof(tx_out->amount) + sizeof(tx_out->pub), tx_out->hash))
		return (free(tx_out), NULL);
	return (tx_out);
}
