#include <stdio.h>
#include <stdlib.h>

/**
 * is_number - Checks if a string contains only digits.
 * @str: String to check.
 *
 * Return: 1 if the string contains only digits, 0 otherwise.
 */
int is_number(char *str)
{
	int i;

	i = 0;

	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}

	return (1);
}

/**
 * main - Adds positive numbers.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char *argv[])
{
	int i;
	int sum;

	sum = 0;

	for (i = 1; i < argc; i++)
	{
		if (!is_number(argv[i]))
		{
			printf("Error\n");
			return (1);
		}

		sum += atoi(argv[i]);
	}

	printf("%d\n", sum);

	return (0);
}
