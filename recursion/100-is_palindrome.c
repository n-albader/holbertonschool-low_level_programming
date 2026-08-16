#include "main.h"

/**
 * string_length - returns the length of a string
 * @s: string to measure
 *
 * Return: length of the string
 */
int string_length(char *s)
{
	if (*s == '\0')
		return (0);

	return (1 + string_length(s + 1));
}

/**
 * palindrome_helper - checks if a string is a palindrome
 * @s: string to check
 * @left: left index
 * @right: right index
 *
 * Return: 1 if palindrome, 0 otherwise
 */
int palindrome_helper(char *s, int left, int right)
{
	if (left >= right)
		return (1);

	if (s[left] != s[right])
		return (0);

	return (palindrome_helper(s, left + 1, right - 1));
}

/**
 * is_palindrome - returns 1 if a string is a palindrome
 * @s: string to check
 *
 * Return: 1 if palindrome, 0 otherwise
 */
int is_palindrome(char *s)
{
	return (palindrome_helper(s, 0, string_length(s) - 1));
}
