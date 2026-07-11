#include <stdio.h>
#include <math.h>

/**
 * main - prints the largest prime factor of 612852475143
 *
 * Return: Always 0
 */
int main(void)
{
	unsigned long n = 612852475143;
	unsigned long factor;
	unsigned long largest = 0;

	while (n % 2 == 0)
	{
		largest = 2;
		n /= 2;
	}

	for (factor = 3; factor <= sqrt(n); factor += 2)
	{
		while (n % factor == 0)
		{
			largest = factor;
			n /= factor;
		}
	}

	if (n > 2)
		largest = n;

	printf("%lu\n", largest);

	return (0);
}
