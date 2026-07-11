#include "main.h"

/**
 * print_number - prints an integer
 * @n: number to print
 */
void print_number(int n)
{
	unsigned int num;
	unsigned int div = 1;

	if (n < 0)
	{
		_putchar('-');
		num = -n;
	}
	else
	{
		num = n;
	}

	while (num / div >= 10)
		div *= 10;

	while (div != 0)
	{
		_putchar((num / div) + '0');
		num %= div;
		div /= 10;
	}
}
