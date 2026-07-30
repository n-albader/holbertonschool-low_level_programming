#include "3-calc.h"

/**
 * main - performs simple operations
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	int (*operation)(int, int);

	if (argc != 4)
	{
		printf("Error\n");
		exit(98);
	}

	operation = get_op_func(argv[2]);

	if (operation == NULL)
	{
		printf("Error\n");
		exit(99);
	}

	if (((argv[2][0] == '/' && atoi(argv[3]) == 0) ||
	     (argv[2][0] == '%' && atoi(argv[3]) == 0)))
	{
		printf("Error\n");
		exit(100);
	}

	printf("%d\n", operation(atoi(argv[1]), atoi(argv[3])));

	return (0);
}
