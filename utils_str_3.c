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
