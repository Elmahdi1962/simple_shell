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
	int exp = 1, i;
	char *str1 = NULL;

	if ((str != NULL) && (*str == '+'))
		str1 = str + 1;
	if ((str1 == NULL) || (str_len(str1) > str_len(MAX_INT_STR)))
		return (FALSE);

	for (i = str_len(str1) - 1; i >= 0; i--)
	{
		if (is_digit(*(str1 + i)))
		{
			val += ((*(str1 + i) - '0') * exp);
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

/**
 * contains_char - Checks if the given string contains a given character
 * @str: The string to check
 * @c: The character to look for
 *
 * Return: TRUE if the character exists, otherwise FALSE
 */
char contains_char(char *str, char c)
{
	int i;

	if (str == NULL)
		return (FALSE);
	for (i = 0; *(str + i) != '\0'; i++)
	{
		if (*(str + i) == c)
			return (TRUE);
	}
	return (FALSE);
}
