#include "main.h"

/**
 * is_valid_uint - Checks if the given string is a valid unsigned integer
 * @str: The string to check
 *
 * Return: TRUE or FALSE
 */
char is_valid_uint(char *str)
{
	long val = 0;
	int exp = 1;
	int i;

	if ((str == NULL) || (str_len(str) > str_len(MAX_INT_STR)))
		return (FALSE);
	for (i = str_len(str) - 1; i >= 0; i--)
	{
		if (is_digit(*(str + i)))
		{
			val += ((*(str + i) - '0') * exp);
			exp *= 10;
		}
		else
		{
			return (FALSE);
		}
	}
	if (val > INT_MAX)
		return (FALSE);
	return (TRUE);
}
