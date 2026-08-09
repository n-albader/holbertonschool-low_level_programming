#include "lists.h"
#include <stdlib.h>

/**
 * insert_dnodeint_at_index - inserts a node at a given index
 * @h: pointer to the head of the list
 * @idx: index where the new node should be inserted
 * @n: value to store in the new node
 *
 * Return: address of the new node, or NULL if it failed
 */
dlistint_t *insert_dnodeint_at_index(dlistint_t **h,
		unsigned int idx, int n)
{
	dlistint_t *new;
	dlistint_t *current;
	unsigned int i = 0;

	if (h == NULL)
		return (NULL);

	if (idx == 0)
		return (add_dnodeint(h, n));

	current = *h;

	while (current != NULL && i < idx)
	{
		current = current->next;
		i++;
	}

	if (i < idx)
		return (NULL);

	if (current == NULL)
		return (add_dnodeint_end(h, n));

	new = malloc(sizeof(dlistint_t));
	if (new == NULL)
		return (NULL);

	new->n = n;
	new->prev = current->prev;
	new->next = current;

	if (current->prev != NULL)
		current->prev->next = new;

	current->prev = new;

	return (new);
}
