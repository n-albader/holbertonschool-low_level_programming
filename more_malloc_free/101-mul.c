#include "main.h"
#include <stdlib.h>

/**
 * _errors - handles errors for main
 */
void _errors(void)
{
	char *err = "Error\n";
	int i = 0;

	while (err[i])
	{
		_putchar(err[i]);
		i++;
	}
	exit(98);
}

/**
 * _is_digit - checks if a string contains only digits
 * @s: string to be evaluated
 *
 * Return: 1 if all digits, 0 otherwise
 */
int _is_digit(char *s)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * _strlen - returns the length of a string
 * @s: string to evaluate
 *
 * Return: the length of the string
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * multiply - performs positional multiplication on string digits
 * @s1: first number string
 * @s2: second number string
 * @result: array storing result digits
 * @len1: length of s1
 * @len2: length of s2
 */
void multiply(char *s1, char *s2, int *result, int len1, int len2)
{
	int i, j, digit1, digit2, carry;

	for (i = len1 - 1; i >= 0; i--)
	{
		digit1 = s1[i] - '0';
		carry = 0;
		for (j = len2 - 1; j >= 0; j--)
		{
			digit2 = s2[j] - '0';
			carry += result[i + j + 1] + (digit1 * digit2);
			result[i + j + 1] = carry % 10;
			carry /= 10;
		}
		if (carry > 0)
			result[i + j + 1] += carry;
	}
}

/**
 * print_result - prints the digits of the result array
 * @result: array containing result digits
 * @len: total size of the result array
 */
void print_result(int *result, int len)
{
	int i, printed = 0;

	for (i = 0; i < len; i++)
	{
		if (result[i])
			printed = 1;
		if (printed)
			_putchar(result[i] + '0');
	}
	if (!printed)
		_putchar('0');
	_putchar('\n');
}

/**
 * main - multiplies two positive numbers
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: always 0 (Success)
 */
int main(int argc, char *argv[])
{
	char *s1, *s2;
	int len1, len2, len, i, *result;

	if (argc != 3 || !_is_digit(argv[1]) || !_is_digit(argv[2]))
		_errors();

	s1 = argv[1];
	s2 = argv[2];
	len1 = _strlen(s1);
	len2 = _strlen(s2);
	len = len1 + len2;

	result = malloc(sizeof(int) * len);
	if (!result)
		return (1);

	for (i = 0; i < len; i++)
		result[i] = 0;

	multiply(s1, s2, result, len1, len2);
	print_result(result, len);
	free(result);

	return (0);
}
