#include <stdlib.h>
#include "dog.h"

/**
 * str_len - Returns the length of a string
 * @s: String
 *
 * Return: Length of the string
 */
int str_len(char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * str_copy - Copies a string
 * @dest: Destination
 * @src: Source
 *
 * Return: Pointer to dest
 */
char *str_copy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return (dest);
}

/**
 * new_dog - Creates a new dog
 * @name: Dog's name
 * @age: Dog's age
 * @owner: Dog's owner
 *
 * Return: Pointer to the new dog, or NULL if it fails
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *dog;

	if (name == NULL || owner == NULL)
		return (NULL);

	dog = malloc(sizeof(dog_t));
	if (dog == NULL)
		return (NULL);

	dog->name = malloc((str_len(name) + 1) * sizeof(char));
	if (dog->name == NULL)
	{
		free(dog);
		return (NULL);
	}

	dog->owner = malloc((str_len(owner) + 1) * sizeof(char));
	if (dog->owner == NULL)
	{
		free(dog->name);
		free(dog);
		return (NULL);
	}

	str_copy(dog->name, name);
	str_copy(dog->owner, owner);

	dog->age = age;

	return (dog);
}
