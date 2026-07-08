#include "main.h"

/**
 * times_table - prints the 9 times table
 */
void times_table(void)
{
	int row, col, result;

	row = 0;

	while (row <= 9)
	{
		col = 0;

		while (col <= 9)
		{
			result = row * col;

			if (col == 0)
			{
				_putchar(result + '0');
			}
			else
			{
				_putchar(',');
				_putchar(' ');

				if (result < 10)
				{
					_putchar(' ');
					_putchar(result + '0');
				}
				else
				{
					_putchar((result / 10) + '0');
					_putchar((result % 10) + '0');
				}
			}

			col++;
		}

		_putchar('\n');
		row++;
	}
}
