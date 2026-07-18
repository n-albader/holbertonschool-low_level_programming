#include "main.h"

/**
 * infinite_add - adds two numbers
 * @n1: first number
 * @n2: second number
 * @r: buffer to store the result
 * @size_r: size of buffer
 *
 * Return: pointer to result, or 0 if buffer is too small
 */
char *infinite_add(char *n1, char *n2, char *r, int size_r)
{
	int len1 = 0, len2 = 0;
	int i, j, k, sum, carry = 0;

	while (n1[len1])
		len1++;
	while (n2[len2])
		len2++;

	i = len1 - 1;
	j = len2 - 1;
	k = size_r - 2;

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

	k++;

	if (k == 0)
		return (r);

	i = 0;
	while (r[k])
	{
		r[i] = r[k];
		i++;
		k++;
	}
	r[i] = '\0';

	return (r);
}
