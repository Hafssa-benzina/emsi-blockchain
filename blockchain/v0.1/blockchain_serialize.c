#include "blockchain.h"
/**
*blockchain points to the Blockchain to be serialized,
*path contains the path to a file to serialize the Blockchain into
*If path points to an existing file, it must be overwritten
*the function must return 0 upon success, or -1 upon failure
*/
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
  int file, i, size;
	uint8_t endianness = _get_endianness();
	if (!blockchain || !blockchain->chain || !path)
		return (-1);
	size = llist_size(blockchain->chain);
	file = open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (file == -1)
		return (-1);
	if (write(file, HBLK_MAGIC, strlen(HBLK_MAGIC)) != strlen(HBLK_MAGIC))
		goto end;
	if (write(file, HBLK_VERSION, strlen(HBLK_VERSION)) != strlen(HBLK_VERSION))
		goto end;
	if (write(file, &endianness, 1) != 1)
		goto end;
	if (write(file, &size, 4) != 4)
		goto end;
	for (i = 0; i < size; i++)
	{
		block_t *block = llist_get_node_at(blockchain->chain, i);

		if (!block)
			goto end;
		if (write(file, &(block->info), sizeof(block->info)) != sizeof(block->info))
			goto end;
		if (write(file, &(block->data.len), 4) != 4)
			goto end;
		if (write(file, block->data.buffer, block->data.len) != block->data.len)
			goto end;
		if (write(file, block->hash, SHA256_DIGEST_LENGTH) != SHA256_DIGEST_LENGTH)
			goto end;
	}
	return (close(file), 0);
end:
	return (close(file), -1);
}
