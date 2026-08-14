#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_tables.h"

/**
 * shash_table_create - creates a sorted hash table
 * @size: size of the array
 *
 * Return: pointer to the new hash table, or NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;

	if (size == 0)
		return (NULL);

	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->array = calloc(size, sizeof(shash_node_t *));
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	ht->size = size;
	ht->shead = NULL;
	ht->stail = NULL;

	return (ht);
}

/**
 * sorted_insert - inserts a node in the sorted list
 * @ht: sorted hash table
 * @node: node to insert
 */
void sorted_insert(shash_table_t *ht, shash_node_t *node)
{
	shash_node_t *current;

	current = ht->shead;

	while (current != NULL && strcmp(current->key, node->key) < 0)
		current = current->snext;

	if (current == NULL)
	{
		node->sprev = ht->stail;
		node->snext = NULL;

		if (ht->stail != NULL)
			ht->stail->snext = node;
		else
			ht->shead = node;

		ht->stail = node;
	}
	else
	{
		node->snext = current;
		node->sprev = current->sprev;

		if (current->sprev != NULL)
			current->sprev->snext = node;
		else
			ht->shead = node;

		current->sprev = node;
	}
}

/**
 * create_shash_node - creates a new sorted hash node
 * @key: key of the node
 * @value: value of the node
 *
 * Return: new node, or NULL on failure
 */
shash_node_t *create_shash_node(const char *key, const char *value)
{
	shash_node_t *node;

	node = malloc(sizeof(shash_node_t));
	if (node == NULL)
		return (NULL);

	node->key = strdup(key);
	if (node->key == NULL)
	{
		free(node);
		return (NULL);
	}

	node->value = strdup(value);
	if (node->value == NULL)
	{
		free(node->key);
		free(node);
		return (NULL);
	}

	node->next = NULL;
	node->sprev = NULL;
	node->snext = NULL;

	return (node);
}

/**
 * shash_table_set - adds or updates an element
 * @ht: sorted hash table
 * @key: key of the element
 * @value: value associated with the key
 *
 * Return: 1 if successful, 0 otherwise
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	shash_node_t *current;
	shash_node_t *node;
	char *new_value;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	current = ht->array[index];

	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			new_value = strdup(value);
			if (new_value == NULL)
				return (0);

			free(current->value);
			current->value = new_value;

			return (1);
		}

		current = current->next;
	}

	node = create_shash_node(key, value);
	if (node == NULL)
		return (0);

	node->next = ht->array[index];
	ht->array[index] = node;

	sorted_insert(ht, node);

	return (1);
}

/**
 * shash_table_get - retrieves a value associated with a key
 * @ht: sorted hash table
 * @key: key to search for
 *
 * Return: value associated with key, or NULL
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	shash_node_t *current;

	if (ht == NULL || key == NULL)
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);
	current = ht->array[index];

	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
			return (current->value);

		current = current->next;
	}

	return (NULL);
}

/**
 * shash_table_print - prints the sorted hash table
 * @ht: sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *current;
	int first;

	if (ht == NULL)
		return;

	printf("{");
	first = 1;
	current = ht->shead;

	while (current != NULL)
	{
		if (!first)
			printf(", ");

		printf("'%s': '%s'", current->key, current->value);
		first = 0;
		current = current->snext;
	}

	printf("}\n");
}

/**
 * shash_table_print_rev - prints the sorted hash table in reverse
 * @ht: sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *current;
	int first;

	if (ht == NULL)
		return;

	printf("{");
	first = 1;
	current = ht->stail;

	while (current != NULL)
	{
		if (!first)
			printf(", ");

		printf("'%s': '%s'", current->key, current->value);
		first = 0;
		current = current->sprev;
	}

	printf("}\n");
}

/**
 * shash_table_delete - deletes a sorted hash table
 * @ht: sorted hash table
 */
void shash_table_delete(shash_table_t *ht)
{
	unsigned long int i;
	shash_node_t *current;
	shash_node_t *next;

	if (ht == NULL)
		return;

	for (i = 0; i < ht->size; i++)
	{
		current = ht->array[i];

		while (current != NULL)
		{
			next = current->next;

			free(current->key);
			free(current->value);
			free(current);

			current = next;
		}
	}

	free(ht->array);
	free(ht);
}
