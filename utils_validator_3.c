#include "main.h"

/**
 * is_valid_uint - Checks if the given string is a valid unsigned integer
 * @str: The string to check
 * @res_out: The pointer to the output number
 *
 * Return: TRUE or FALSE
 */
char is_valid_uint(char *str, int *res_out)
{
	long val = 0;

	if ((str != NULL) && (*str == '+'))
		str += 1;
	while ((str != NULL) && ((*str == '0') && (*(str + 1) != '\0')))
	{
		str++;
	}
	if (*str == '\0')
		return (FALSE);
	while (*str != '\0' && val < INT_MAX)
	{
		if (!is_digit(*str))
			return (FALSE);
		val = (val * 10) + (*str - '0');
		str++;
	}
	if (val <= INT_MAX)
	{
		*res_out = val;
		return (TRUE);
	}
	return (FALSE);
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
