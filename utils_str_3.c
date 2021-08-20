#include "main.h"

/**
 * swap - Swaps two numbers
 * @x: digit
 * @y: digit
 */
void swap(char *x, char *y)
{
	char t = *x;

	*x = *y;
	*y = t;
}

/**
 * reverse -Reverses a `buffer[i…j]`
 * @buffer: buffer to reverse
 * @i: first digit or index
 * @j: last digit or index
 *
 * Return: The reversed buffer
 */
char *reverse(char *buffer, int i, int j)
{
	while (i < j)
	{
		swap(&buffer[i++], &buffer[j--]);
	}

	return buffer;
}

/**
 * str_in_arr - Checks if a string is in an array
 * @arr: The array to look through
 * @n: The length of the array
 * @str: The string to search for
 *
 * Return: TRUE if the string is in the array, otherwise FALSE
 */
char str_in_arr(char **arr, int n, char *str)
{
	int i;

	for (i = 0; (arr != NULL) && (i < n); i++)
	{
		if (str_eql(*(arr + i), str))
			return (TRUE);
	}
	return (FALSE);
}
