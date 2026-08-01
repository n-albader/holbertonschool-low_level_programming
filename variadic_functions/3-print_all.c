#include "variadic_functions.h"
#include <stdio.h>

/**
 * print_char - Prints a char
 * @args: Argument list
 * @sep: Separator
 */
void print_char(va_list *args, char *sep)
{
	printf("%s%c", sep, va_arg(*args, int));
}

/**
 * print_int - Prints an int
 * @args: Argument list
 * @sep: Separator
 */
void print_int(va_list *args, char *sep)
{
	printf("%s%d", sep, va_arg(*args, int));
}

/**
 * print_float - Prints a float
 * @args: Argument list
 * @sep: Separator
 */
void print_float(va_list *args, char *sep)
{
	printf("%s%f", sep, va_arg(*args, double));
}

/**
 * print_string - Prints a string
 * @args: Argument list
 * @sep: Separator
 */
void print_string(va_list *args, char *sep)
{
	char *str;

	str = va_arg(*args, char *);

	if (str == NULL)
		str = "(nil)";

	printf("%s%s", sep, str);
}

/**
 * print_all - Prints anything
 * @format: List of argument types
 */
void print_all(const char * const format, ...)
{
	va_list args;
	printer_t p[] = {
		{'c', print_char},
		{'i', print_int},
		{'f', print_float},
		{'s', print_string},
		{'\0', NULL}
	};
	char *sep;
	int i;
	int j;

	va_start(args, format);
	sep = "";
	i = 0;

	while (format && format[i])
	{
		j = 0;
		while (p[j].type)
		{
			if (format[i] == p[j].type)
			{
				p[j].func(&args, sep);
				sep = ", ";
				break;
			}
			j++;
		}
		i++;
	}

	va_end(args);
	printf("\n");
}
