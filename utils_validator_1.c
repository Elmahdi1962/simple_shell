#include "main.h"

/**
 * str_is_num - checks if the string is a number
 * @str: the string to check
 *
 * Return: true or false
 */
char str_is_num(char *str)
{
	char *string = str;
	int firstc = 1;

	while (*string != '\0')
	{
		if (firstc)
		{
			if (*string == '-' || *string == '+')
				string++;
			firstc = 0;
			continue;
		}
		if (*string >= '0' && *string <= '9')
			string++;
		else
			return (FALSE);
	}
	return (TRUE);
}
