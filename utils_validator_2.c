#include "main.h"

/**
 * is_alias - Checks if the given string is an available alias
 * @str: The string to check
 *
 * Return: TRUE or FALSE if the name exists
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
 * is_alias_name - Checks if the given string is a valid alias name
 * @str: The string to check
 *
 * Return: TRUE if it's valid, otherwise FALSE
 */
char is_alias_name(char *str)
{
	int i = 0;

	while ((str != NULL) && (*(str + i) != '\0'))
	{
		if (is_digit(*(str + i))
			|| is_letter(*(str + i))
			|| (*(str + i) == '_')
			|| (*(str + i) == '!')
			|| (*(str + i) == '%')
			|| (*(str + i) == ',')
			|| (*(str + i) == '@'))
			i++;
		else
			break;
	}
	if (str != NULL && *(str + i) == '\0')
		return (TRUE);
	else
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
char is_alias_assignment(char *str, char **name_out, char **value_out)
{
	int i = 0, j, name_len = 0, value_len = 0;
	char is_assignment = FALSE;

	printf("-- checking name val pair\n");
	for (; (str != NULL) && (*(str + i) != '='); i++)
		name_len++;
	is_assignment = ((str != NULL) && (*(str + i) == '=')) ? TRUE : FALSE;
	i++;
	for (; (str != NULL) && (*(str + i) != '\0'); i++)
		value_len++;
	if (name_out != NULL)
	{
		*name_out = malloc(sizeof(char) * (name_len + 1));
		if (*name_out != NULL)
		{
			for (j = 0, i = 0; j < name_len; j++)
				*(*name_out + j) = *(str + i), i++;
			*(*name_out + j) = '\0', i++;
		}
		if (value_out != NULL)
		{
			*value_out = malloc(sizeof(char) * (value_len + 1));
			if (*value_out != NULL)
			{
				for (j = 0; j < value_len; j++)
					*(*value_out + j) = *(str + i), i++;
				*(*value_out + j) = '\0';
			}
		}
	}
	printf("(i_a_a) name: %s, val: %s\n", *name_out, *value_out);
	return (is_assignment);
}

/** is_regular_file - check if the path is a file or a directory
 * @path: file or folder path
 *
 * Return: 1 if is a regular file 0 if not
 */
int is_regular_file(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}
