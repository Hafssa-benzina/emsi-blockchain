#include "blockchain.h"
/**
 * blockchain_deserialize - deserializes blockchain from file
 * @path: path to serialized blockchain file
 * Return: pointer to deserialized blockchain or null
 */
blockchain_t *blockchain_deserialize(char const *path)
{
	int f;
	blockchain_t *chain = NULL;
	uint8_t endianness;
	char buf[4096] = {0};
	uint32_t size;

	if (!path)
		return (NULL);
	f = open(path, O_RDONLY);
	if (f == -1)
		return (NULL);
	if (read(f, buf, strlen(HBLK_MAGIC)) != strlen(HBLK_MAGIC) ||
	    strcmp(buf, HBLK_MAGIC))
	{
		free(chain);
		close(f);
		return (NULL);
	}
	buf[strlen(HBLK_VERSION)] = 0;
	if (read(f, buf, strlen(HBLK_VERSION)) != strlen(HBLK_VERSION) ||
	    strcmp(buf, HBLK_VERSION))
	{
		free(chain);
		close(f);
		return (NULL);
	}
	chain = calloc(1, sizeof(*chain));
	if (!chain)
	{
		free(chain);
		close(f);
		return (NULL);
	}
	if (read(f, &endianness, 1) != 1)
	{
		free(chain);
		close(f);
		return (NULL);
	}
	endianness = endianness != _get_endianness();
	if (read(f, &size, 4) != 4)
	{
		free(chain);
		close(f);
		return (NULL);
	}
	CHECK_ENDIAN(size);
	chain->chain = deserialize_blocks(f, size, endianness);
	if (!chain)
	{
		free(chain);
		close(f);
		return (NULL);
	}
	return (close(f), chain);
}

/**
 * deserialize_blocks - deserializes all the blocks in the file
 * @f: open f to save file
 * @size: number of blocks in the file
 * @endianness: if endianess needs switching
 * Return: pointer to list of blocks or NULL
 */
llist_t *deserialize_blocks(int f, uint32_t size, uint8_t endianness)
{
	block_t *block;
	llist_t *list = llist_create(MT_SUPPORT_TRUE);
	uint32_t i = 0;

	if (!list)
		return (NULL);
	for (i = 0; i < size; i++)
	{
		block = calloc(1, sizeof(*block));
		if (!block)
		{
			free(block);
			llist_destroy(list, 1, NULL);
			return (NULL);
		}
		if (read(f, &(block->info), sizeof(block->info)) != sizeof(block->info))
		{
			free(block);
			llist_destroy(list, 1, NULL);
			return (NULL);
		}
		CHECK_ENDIAN(block->info.index);
		CHECK_ENDIAN(block->info.difficulty);
		CHECK_ENDIAN(block->info.timestamp);
		CHECK_ENDIAN(block->info.nonce);
		if (read(fd, &(block->data.len), 4) != 4)
		{
			free(block);
			llist_destroy(list, 1, NULL);
			return (NULL);
		}
		CHECK_ENDIAN(block->data.len);
		if (read(f, block->data.buffer, block->data.len) != block->data.len)
		{
			free(block);
			llist_destroy(list, 1, NULL);
			return (NULL);
		}
		if (read(f, block->hash, SHA256_DIGEST_LENGTH) !=
		    SHA256_DIGEST_LENGTH)
		{
			free(block);
			llist_destroy(list, 1, NULL);
			return (NULL);
		}
		if (llist_add_node(list, block, ADD_NODE_REAR))
		{
			free(block);
			llist_destroy(list, 1, NULL);
			return (NULL);
		}
	}
	return (list);
}
