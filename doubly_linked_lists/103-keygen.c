#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - generates a key for crackme5
 * @argc: number of arguments
 * @argv: arguments
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *charset;
	char key[7];
	int len, sum, product, max;
	int i;
	int r;

	charset = "A-CHRDw8H7lNS0E9BH2TibgpnMHVys5XzvtHOGJcYLU+H4mjW6fxqHZeF3Qa1rHPhdKIoukH";

	if (argc != 2)
		return (1);

	len = strlen(argv[1]);

	/* First character */
	key[0] = charset[(len ^ 0x3B) & 0x3F];

	/* Second character: sum of username characters */
	sum = 0;
	for (i = 0; i < len; i++)
		sum += argv[1][i];

	key[1] = charset[(sum ^ 0x4F) & 0x3F];

	/* Third character: product of username characters */
	product = 1;
	for (i = 0; i < len; i++)
		product *= argv[1][i];

	key[2] = charset[(product ^ 0x55) & 0x3F];

	/* Fourth character: random value based on largest character */
	max = argv[1][0];
	for (i = 0; i < len; i++)
	{
		if (argv[1][i] > max)
			max = argv[1][i];
	}

	srand(max ^ 0x0E);
	r = rand();
	key[3] = charset[r & 0x3F];

	/* Fifth character: sum of squares */
	sum = 0;
	for (i = 0; i < len; i++)
		sum += argv[1][i] * argv[1][i];

	key[4] = charset[(sum ^ 0xEF) & 0x3F];

	/* Sixth character: random value */
	r = 0;
	for (i = 0; i < key[0]; i++)
		r = rand();

	key[5] = charset[(r ^ 0xE5) & 0x3F];

	key[6] = '\0';

	printf("%s", key);

	return (0);
}
