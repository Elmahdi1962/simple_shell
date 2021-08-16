#include "main.h"

/**
 * is_alias - Checks if the given string is an alias
 * @str: The string to check
 *
 * Return: TRUE or FALSE
 */
char is_alias(char *str)
{
	int n = 0;
	alias_t **aliases = get_aliases(&n);
	int i;

	if (aliases != NULL)
	{
		for (i = 0; i < n; i++)
		{
			if (str_cmp(str, (*(aliases + i))->name) == 0)
				return (TRUE);
		}
	}
	return (FALSE);
}

