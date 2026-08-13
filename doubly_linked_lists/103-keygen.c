#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - Generates a key for crackme5 based on the given username
 * @argc: Number of arguments passed
 * @argv: Array of argument strings
 *
 * Return: Always 0 on success, 1 on wrong argument count
 */
int main(int argc, char *argv[])
{
	char key[7], *u, *l;
	int len, i, ch, max;
	long int sum = 0, prod = 1, sum_sq = 0;

	if (argc != 2)
		return (1);

	u = argv[1];
	len = strlen(u);
	l = "A-CHRDw87lNS0E9B2TibgpnMVys5XzvtOGJcYLU+4mjW6fxqZeF3Qa1rPhdKIouk";
	max = u[0];

	for (i = 0; i < len; i++)
	{
		sum += u[i];
		prod *= u[i];
		if (u[i] > max)
			max = u[i];
		sum_sq += (u[i] * u[i]);
	}

	key[0] = l[(len ^ 59) & 63];
	key[1] = l[(sum ^ 79) & 63];
	key[2] = l[(prod ^ 85) & 63];

	srand(max ^ 14);
	key[3] = l[rand() & 63];
	key[4] = l[(sum_sq ^ 239) & 63];

	for (i = 0, ch = 0; i < u[0]; i++)
		ch = rand();

	key[5] = l[(ch ^ 229) & 63];
	key[6] = '\0';

	printf("%s", key);
	return (0);
}
