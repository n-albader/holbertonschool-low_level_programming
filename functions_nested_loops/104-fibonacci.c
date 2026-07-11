#include <stdio.h>

/**
 * main - prints the first 98 Fibonacci numbers
 *
 * Return: Always 0
 */
int main(void)
{
	unsigned long a1, a2, b1, b2, c1, c2;
	int i;

	a1 = 0;
	a2 = 1;
	b1 = 0;
	b2 = 2;

	printf("1, 2");

	for (i = 3; i <= 98; i++)
	{
		c1 = a1 + b1;
		c2 = a2 + b2;

		if (c2 >= 1000000000)
		{
			c1 += c2 / 1000000000;
			c2 %= 1000000000;
		}

		if (c1 > 0)
			printf(", %lu%09lu", c1, c2);
		else
			printf(", %lu", c2);

		a1 = b1;
		a2 = b2;
		b1 = c1;
		b2 = c2;
	}

	printf("\n");

	return (0);
}
