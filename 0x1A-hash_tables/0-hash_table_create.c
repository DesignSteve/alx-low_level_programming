#include "hash_tables.h"

/**
 * hash_table_create - generates a hash table
 * @size: The sixe of the array to be created
 * Return: Pointer to the created hash table or return NULL on failure
 */
hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *hash_table = NULL;
	unsigned long int p;

	if (size == 0)
	{
		return (NULL);
	}

	/* Allocate memory to the hash table */
	hash_table = malloc(sizeof(hash_table_t));
	if (hash_table == NULL)
	{
		return (NULL);
	}

	/* Allocate memory for array of hash nodes */
	hash_table->array = malloc(sizeof(hash_node_t *) * size);
	if (hash_table->array == NULL)
	{
		free(hash_table);
		return (NULL);
	}

	hash_table->size = size;

	/* Initialize all hash node pointers to NULL */
	for (p = 0; p < size; p++)
	{
		hash_table->array[p] = NULL;
	}

	return (hash_table);
}
