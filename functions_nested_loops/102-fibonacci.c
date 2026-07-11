#include <stdio.h>

/**
 * main - prints the first 50 Fibonacci numbers
 *
 * Return: Always 0
 */
int main(void)
{
	unsigned long int a = 1, b = 2, next;
	int i;

	for (i = 1; i <= 50; i++)
	{
		if (i == 1)
			printf("%lu", a);
		else if (i == 2)
			printf(", %lu", b);
		else
		{
			next = a + b;
			printf(", %lu", next);
			a = b;
			b = next;
		}
	}

	printf("\n");

	return (0);
}
