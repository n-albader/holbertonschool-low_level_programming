#include "main.h"

/**
 * str_len - returns the length of a string
 * @s: string
 *
 * Return: length
 */
int str_len(char *s)
{
	int len = 0;

	while (s[len])
		len++;

	return (len);
}

/**
 * infinite_add - adds two numbers
 * @n1: first number
 * @n2: second number
 * @r: buffer
 * @size_r: buffer size
 *
 * Return: pointer to result or 0
 */
char *infinite_add(char *n1, char *n2, char *r, int size_r)
{
	int i = str_len(n1) - 1;
	int j = str_len(n2) - 1;
	int k = size_r - 2;
	int sum, carry = 0, start = 0;

	r[size_r - 1] = '\0';

	while (i >= 0 || j >= 0 || carry)
	{
		sum = carry;

		if (i >= 0)
			sum += n1[i--] - '0';
		if (j >= 0)
			sum += n2[j--] - '0';
		if (k < 0)
			return (0);

		r[k--] = (sum % 10) + '0';
		carry = sum / 10;
	}

	start = ++k;
	k = 0;

	while (r[start])
		r[k++] = r[start++];

	r[k] = '\0';

	return (r);
}
