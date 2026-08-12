#include <stdio.h>
#include <stdlib.h>

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
	int len, i, sum, product, max;
	int value;

	charset = "A-CHRDw8H7lNS0E9BH2TibgpnMHVys5XzvtHOGJcYLU+H4mjW6fxqHZeF3Qa1rHPhdKIoukH";

	if (argc != 2)
		return (1);

	/* Get username length */
	len = 0;
	while (argv[1][len] != '\0')
		len++;

	/* First character */
	value = (len ^ 0x3B) & 0x3F;
	key[0] = charset[value];

	/* Second character: sum of all characters */
	sum = 0;
	for (i = 0; i < len; i++)
		sum += argv[1][i];

	value = (sum ^ 0x4F) & 0x3F;
	key[1] = charset[value];

	/* Third character: product of all characters */
	product = 1;
	for (i = 0; i < len; i++)
		product *= argv[1][i];

	value = (product ^ 0x55) & 0x3F;
	key[2] = charset[value];

	/* Fourth character: largest character */
	max = argv[1][0];
	for (i = 0; i < len; i++)
	{
		if (argv[1][i] > max)
			max = argv[1][i];
	}

	srand(max ^ 0x0E);
	value = rand() & 0x3F;
	key[3] = charset[value];

	/* Fifth character: sum of squares */
	sum = 0;
	for (i = 0; i < len; i++)
		sum += argv[1][i] * argv[1][i];

	value = (sum ^ 0xEF) & 0x3F;
	key[4] = charset[value];

	/*
	 * Sixth character:
	 * use the first character of username
	 * as the number of rand() calls.
	 */
	value = 0;
	for (i = 0; i < argv[1][0]; i++)
		value = rand();

	value = (value ^ 0xE5) & 0x3F;
	key[5] = charset[value];

	key[6] = '\0';

	printf("%s\n", key);

	return (0);
}
