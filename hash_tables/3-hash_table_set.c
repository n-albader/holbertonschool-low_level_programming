#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/**
 * update_value - updates the value of an existing node
 * @node: node to update
 * @value: new value
 *
 * Return: 1 if successful, 0 otherwise
 */
int update_value(hash_node_t *node, const char *value)
{
	char *new_value;

	new_value = strdup(value);
	if (new_value == NULL)
		return (0);

	free(node->value);
	node->value = new_value;

	return (1);
}

/**
 * create_node - creates a new hash node
 * @key: key of the node
 * @value: value of the node
 *
 * Return: pointer to the new node, or NULL if it fails
 */
hash_node_t *create_node(const char *key, const char *value)
{
	hash_node_t *new_node;

	new_node = malloc(sizeof(hash_node_t));
	if (new_node == NULL)
		return (NULL);

	new_node->key = strdup(key);
	if (new_node->key == NULL)
	{
		free(new_node);
		return (NULL);
	}

	new_node->value = strdup(value);
	if (new_node->value == NULL)
	{
		free(new_node->key);
		free(new_node);
		return (NULL);
	}

	new_node->next = NULL;

	return (new_node);
}

/**
 * hash_table_set - adds or updates an element in a hash table
 * @ht: hash table
 * @key: key of the element
 * @value: value associated with the key
 *
 * Return: 1 if successful, 0 otherwise
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	hash_node_t *current;
	hash_node_t *new_node;
	unsigned long int index;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	current = ht->array[index];

	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
			return (update_value(current, value));

		current = current->next;
	}

	new_node = create_node(key, value);
	if (new_node == NULL)
		return (0);

	new_node->next = ht->array[index];
	ht->array[index] = new_node;

	return (1);
}
