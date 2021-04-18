
#include "blockchain.h"
/**
*path contains the path to a file to load the Blockchain from
*the function must return a pointer to the deserialized Blockchain upon success, or NULL upon failure
*The format of the file to parse is described in the previous task
*Upon any error, the function must fail and return NULL
*/

blockchain_t *blockchain_deserialize(char const *path)
{
	int file;
	blockchain_t *chain = NULL;
	uint8_t endianness;
	char buf[4096] = {0};
	uint32_t size;

	if (!path)
		return (NULL);
	file = open(path, O_RDONLY);
	if (file == -1)
		return (NULL);
	if (read(file, buf, strlen(HBLK_MAGIC)) != strlen(HBLK_MAGIC) ||
	    strcmp(buf, HBLK_MAGIC))
	{
		free(chain);
		close(file);
		return (NULL);
	}
	buf[strlen(HBLK_VERSION)] = 0;
	if (read(file, buf, strlen(HBLK_VERSION)) != strlen(HBLK_VERSION) ||
	    strcmp(buf, HBLK_VERSION))
	{
		free(chain);
		close(file);
		return (NULL);
	}
	chain = calloc(1, sizeof(*chain));
	if (!chain)
	{
		free(chain);
		close(file);
		return (NULL);
	}
	if (read(file, &endianness, 1) != 1)
	{
		free(chain);
		close(file);
		return (NULL);
	}
	endianness = endianness != _get_endianness();
	if (read(file, &size, 4) != 4)
	{
		free(chain);
		close(file);
		return (NULL);
	}
	CHECK_ENDIAN(size);
	chain->chain = deserialize_blocks(file, size, endianness);
	if (!chain)
	{
		free(chain);
		close(file);
		return (NULL);
	}
	return (close(file), chain);
}
llist_t *deserialize_blocks(int file, uint32_t size, uint8_t endianness)
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
		if (read(file, &(block->info), sizeof(block->info)) != sizeof(block->info))
		{
			free(block);
			llist_destroy(list, 1, NULL);
			return (NULL);
		}
		CHECK_ENDIAN(block->info.index);
		CHECK_ENDIAN(block->info.difficulty);
		CHECK_ENDIAN(block->info.timestamp);
		CHECK_ENDIAN(block->info.nonce);
		if (read(file, &(block->data.len), 4) != 4)
		{
			free(block);
			llist_destroy(list, 1, NULL);
			return (NULL);
		}
		CHECK_ENDIAN(block->data.len);
		if (read(file, block->data.buffer, block->data.len) != block->data.len)
		{
			free(block);
			llist_destroy(list, 1, NULL);
			return (NULL);
		}
		if (read(file, block->hash, SHA256_DIGEST_LENGTH) !=
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
