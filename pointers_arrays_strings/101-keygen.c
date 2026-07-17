#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
  int length = 42;
	char key[length + 1];
	int i;
	int a, b;

	/* Start with a known valid key */
	for (i = 0; i < length; i++)
		key[i] = 'B';
	key[length] = '\0';

	/* Seed the random number generator */
	srand((unsigned int)time(NULL));

	/* Randomly modify the key while keeping the checksum constant */
	for (i = 0; i < 100; i++)
	{
		a = rand() % length;
		b = rand() % length;

		if (key[a] > '!' && key[b] < '~')
		{
			key[a]--;
			key[b]++;
		}
	}

	/* Print the key */
	for (i = 0; i < length; i++)
		putchar(key[i]);

	putchar('\n');

	return (0);
}
