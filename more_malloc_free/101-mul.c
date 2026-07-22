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
	int len;

	len = 0;

	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * init_result - Initializes result array
 * @result: Result array
 * @len: Length
 */
void init_result(int *result, int len)
{
	int i;

	for (i = 0; i < len; i++)
		result[i] = 0;
}

/**
 * multiply - Performs multiplication
 * @a: First number
 * @b: Second number
 * @result: Result array
 */
void multiply(char *a, char *b, int *result)
{

	int len1, len2, len, i, j;
  int carry, n1, n2;
  int sum;

	len1 = _strlen(a);
	len2 = _strlen(b);
	len = len1 + len2;

	for (i = len1 - 1; i >= 0; i--)
	{
		carry = 0;
		n1 = a[i] - '0';

		for (j = len2 - 1; j >= 0; j--)
		{
			n2 = b[j] - '0';
			sum = result[i + j + 1] + (n1 * n2) + carry;
			result[i + j + 1] = sum % 10;
			carry = sum / 10;
		}

		result[i] += carry;
	}
}
/**
 * print_result - Prints multiplication result
 * @result: Result array
 * @len: Length
 */
void print_result(int *result, int len)
{
  int i;
  int started;

  started = 0;

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
  int len;
  int *result;

  if (argc != 3)
    print_error();

  if (!is_digit(argv[1])|| !is_digit(argv[2]))
    print_error();

  len = _strlen(argv[1]) + _strlen(argv[2]);

  result = malloc(sizeof(int) * len);
	if (result == NULL)
		print_error();

  init_result(result, len);
  multiply(argv[1], argv[2], result);

  print_result(result, len);

	free(result);

	return (0);
}
