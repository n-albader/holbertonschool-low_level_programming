#include "main.h"

/**
 * _atoi - convert a string to an integer
 * @s: string to convert
 *
 * Return: converted integer
 */
int _atoi(char *s)
{
	int i;
	int sign;
	unsigned int num;
	int started;

	i = 0;
	sign = 1;
	num = 0;
	started = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			started = 1;
			num = (num * 10) + (s[i] - '0');
		}
		else if (started)
			break;
		i++;
	}

	return ((int)(num * sign));
}
