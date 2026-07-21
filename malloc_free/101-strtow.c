#include "main.h"
#include <stdlib.h>

/**
 * count_words - counts the number of words in a string
 * @str: input string
 *
 * Return: number of words
 */
static int count_words(char *str)
{
	int i, words;

	i = 0;
	words = 0;

	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0')
		{
			words++;
			while (str[i] != '\0' && str[i] != ' ')
				i++;
		}
	}
	return (words);
}

/**
 * free_words - frees allocated memory
 * @words: array of words
 * @count: number of allocated words
 *
 * Return: Nothing
 */
static void free_words(char **words, int count)
{
	while (count--)
		free(words[count]);
	free(words);
}

/**
 * fill_words - fills the array with words
 * @words: array of words
 * @str: input string
 * @count: number of words
 *
 * Return: 1 on success, 0 on failure
 */
static int fill_words(char **words, char *str, int count)
{
	int i, j, k, start, len;

	i = 0;
	k = 0;
	while (k < count)
	{
		while (str[i] == ' ')
			i++;
		start = i;
		len = 0;
		while (str[i] != '\0' && str[i] != ' ')
		{
			len++;
			i++;
		}
		words[k] = malloc(sizeof(char) * (len + 1));
		if (words[k] == NULL)
		{
			free_words(words, k);
			return (0);
		}
		for (j = 0; j < len; j++)
			words[k][j] = str[start + j];
		words[k][j] = '\0';
		k++;
	}
	words[k] = NULL;
	return (1);
}

/**
 * strtow - splits a string into words
 * @str: input string
 *
 * Return: pointer to array of words, or NULL
 */
char **strtow(char *str)
{
	char **words;
	int count;

	if (str == NULL || *str == '\0')
		return (NULL);

	count = count_words(str);
	if (count == 0)
		return (NULL);

	words = malloc(sizeof(char *) * (count + 1));
	if (words == NULL)
		return (NULL);

	if (fill_words(words, str, count) == 0)
		return (NULL);

	return (words);
}
