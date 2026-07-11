#include <stdio.h>

/**
 * main - prints the sum of even Fibonacci numbers
 * below 4000000
 *
 * Return: Always 0
 */
int main(void)
{
	unsigned long int a = 1, b = 2, next, sum = 2;

	while (1)
	{
		next = a + b;

		if (next > 4000000)
			break;

		if (next % 2 == 0)
			sum += next;

		a = b;
		b = next;
	}

	printf("%lu\n", sum);

	return (0);
}
