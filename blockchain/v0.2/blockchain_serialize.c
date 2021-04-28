#include "blockchain.h"

/**
 * blockchain_serialize - a function that serializes a Blockchain into a file
 * @blockchain: pointer to blockchain to be serialized
 * @path: the path to a file to serialize the Blockchain into
 *
 * Return: 0 upon success, or -1 upon failure
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	int fd, i, size;
	uint8_t endianness = _get_endianness();

	if (!blockchain || !blockchain->chain || !path)
		return (-1);
	size = llist_size(blockchain->chain);
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (-1);
	if (write(fd, HBLK_MAGIC, strlen(HBLK_MAGIC)) != strlen(HBLK_MAGIC))
		goto end;
	if (write(fd, HBLK_VERSION, strlen(HBLK_VERSION)) != strlen(HBLK_VERSION))
		goto end;
	if (write(fd, &endianness, 1) != 1)
		goto end;
	if (write(fd, &size, 4) != 4)
		goto end;
	for (i = 0; i < size; i++)
	{
		block_t *block = llist_get_node_at(blockchain->chain, i);

		if (!block)
			goto end;
		if (write(fd, &(block->info), sizeof(block->info)) != sizeof(block->info))
			goto end;
		if (write(fd, &(block->data.len), 4) != 4)
			goto end;
		if (write(fd, block->data.buffer, block->data.len) != block->data.len)
			goto end;
		if (write(fd, block->hash, SHA256_DIGEST_LENGTH) !=
		    SHA256_DIGEST_LENGTH)
			goto end;
	}
	return (close(fd), 0);
end:
	return (close(fd), -1);
}
