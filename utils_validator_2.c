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

/**
 * is_name_value_pair - Checks if a string is a name value pair
 * @str: The string to check
 * @name_out: The pointer to the output name
 * @value_out: The pointer to the output value
 *
 * Return: TRUE or FALSE
 */
char is_name_value_pair(char *str, char **name_out, char **value_out)
{
	int i = 0;

	while (*(str + i) != '\0')
	{
		if (i == 0)
		{
			*name_out = read_variable(str, i);
			i += str_len(*name_out);
		}
		else if (*(str + i) == '=')
		{
			read_word(str, &i + 1);
		}
		else
		{
			break;
		}
	}

	if (*(str + i) == '\0')
	{
		return (TRUE);
	}
	else
	{
		if (name_out != NULL)
		{
			if (*name_out)
				free(*name_out);
			name_out = NULL;
		}
		if (value_out != NULL)
		{
			if (*value_out)
				free(*value_out);
			value_out = NULL;
		}
		return (FALSE);
	}
}
