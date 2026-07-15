#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @str: string to modify
 *
 * Return: pointer to the string
 */
char *cap_string(char *str)
{
	int i;
	int j;
	char sep[] = " \t\n,;.!?\"(){}";

	if (str[0] >= 'a' && str[0] <= 'z')
		str[0] -= 32;

	i = 1;
	while (str[i] != '\0')
	{
		j = 0;

		while (sep[j] != '\0')
		{
			if (str[i - 1] == sep[j] &&
			    str[i] >= 'a' &&
			    str[i] <= 'z')
			{
				str[i] -= 32;
			}

			j++;
		}

		i++;
	}

	return (str);
}
