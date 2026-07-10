#include "main.h"

/**
 * print_number - prints a number
 * @num: number to print
 */
void print_number(int num)
{
	if (num >= 100)
	{
		_putchar((num / 100) + '0');
		_putchar(((num / 10) % 10) + '0');
	}
	if (num >= 10)
		_putchar(((num / 10) % 10) + '0');
	_putchar((num % 10) + '0');
}

/**
 * print_times_table - prints the n times table
 * @n: size of the times table
 */
void print_times_table(int n)
{
	int i, j, num;

	if (n < 0 || n > 15)
		return;

	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= n; j++)
		{
			num = i * j;
			if (j != 0)
			{
				_putchar(',');
				_putchar(' ');
				if (num < 10)
				{
					_putchar(' ');
					_putchar(' ');
				}
				else if (num < 100)
					_putchar(' ');
			}
			print_number(num);
		}
		_putchar('\n');
	}
}
