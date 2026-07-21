#include "main.h"
#include <stdlib.h>

/**
 * print_error - Prints Error and exits
 */
void print_error(void)
{
	char error[] = "Error\n";
	int i;

	for (i = 0; error[i] != '\0'; i++)
		_putchar(error[i]);

	exit(98);
}

/**
 * is_digit - Checks if a string contains only digits
 * @s: String to check
 *
 * Return: 1 if true, 0 otherwise
 */
int is_digit(char *s)
{
	int i;

	if (*s == '\0')
		return (0);

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}

	return (1);
}

/**
 * _strlen - Returns length of a string
 * @s: String
 *
 * Return: Length
 */
int _strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;

	return (len);
}

/**
 * main - Multiplies two positive numbers
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	int len1, len2, len, i, j, carry, n1, n2;
	int *result;
	int started = 0;

	if (argc != 3)
		print_error();

	if (!is_digit(argv[1]) || !is_digit(argv[2]))
		print_error();

	len1 = _strlen(argv[1]);
	len2 = _strlen(argv[2]);
	len = len1 + len2;

	result = malloc(sizeof(int) * len);
	if (result == NULL)
		return (1);

	for (i = 0; i < len; i++)
		result[i] = 0;

	for (i = len1 - 1; i >= 0; i--)
	{
		carry = 0;
		n1 = argv[1][i] - '0';

		for (j = len2 - 1; j >= 0; j--)
		{
			n2 = argv[2][j] - '0';
			carry += result[i + j + 1] + (n1 * n2);
			result[i + j + 1] = carry % 10;
			carry /= 10;
		}

		result[i] += carry;
	}

	for (i = 0; i < len; i++)
	{
		if (result[i] != 0)
			started = 1;

		if (started)
			_putchar(result[i] + '0');
	}

	if (!started)
		_putchar('0');

	_putchar('\n');

	free(result);

	return (0);
}
