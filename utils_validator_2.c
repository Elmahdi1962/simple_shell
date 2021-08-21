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
			if (str_eql(str, (*(aliases + i))->name))
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
		if (is_whitespace(*(str + i))
			|| (*(str + i) == '\'')
			|| (*(str + i) == '"')
			|| (*(str + i) == '$')
			|| (*(str + i) == '=')
			|| (*(str + i) == '|')
			|| (*(str + i) == '&')
			|| (*(str + i) == ';')
			|| (*(str + i) == '[')
			|| (*(str + i) == ']')
			|| (*(str + i) == '{')
			|| (*(str + i) == '}')
			|| (*(str + i) == '(')
			|| (*(str + i) == ')')
			|| (*(str + i) == '<')
			|| (*(str + i) == '>'))
		{
			break;
		}
		else
		{
			i++;
		}
	}
	if ((str != NULL) && (*(str + i) == '\0'))
		return (TRUE);
	else
		return (FALSE);
}

/**
 * is_alias_assignment - Checks if a string is an alias assignment \
 * sets the remaining parameters appropriately if TRUE
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
	return (is_assignment);
}

/**
 * is_regular_file - Checks if the path is a file or a directory
 * @path: The file or folder path
 *
 * Return: TRUE if it is a regular file, FALSE if not
 */
int is_regular_file(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

/**
 * is_normal_program - Checks if a command node is a normal program
 * @node: The command node to check
 * @path_out: The pointer to the path of the program if it exists
 *
 * Return: TRUE if it is a normal program, otherwise FALSE
 */
char is_normal_program(cmd_t *node, char **path_out)
{
	char *path = check_path(node->command);

	if (path != NULL)
	{
		if (path_out != NULL)
			*path_out = path;
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}
}
