#include "main.h"

/**
 * str_is_num - checks if the string is a number
 * @str: the string to check
 *
 * Return: true or false
 */
char str_is_num(char *str)
{
	int i = 0;

	if (str == NULL)
		return (FALSE);
	while (*(str + i) != '\0')
	{
		if (((*(str + i) == '-') && (i == 0))
			|| is_digit(*(str + i)))
		{
			i++;
		}
		else
		{
			break;
		}
	}
	return (*(str + i) == '\0' ? TRUE : FALSE);
}

/**
 * is_built_in_cmd - Checks if a command is a built-in command
 * @node: The command node to check
 *
 * Return: TRUE if it is built-in, otherwise FALSE
 */
char is_built_in_cmd(cmd_t *node)
{
	int i;
	char *built_in_cmds[] = {
		"alias",
		"cd",
		"env",
		"exit",
		"help",
		"history",
		"setenv",
		"unsetenv",
		NULL
	};

	for (i = 0; *(built_in_cmds + i) != NULL; i++)
	{
		if (str_eql(node->command, "env"))
			return (node->args_count == 0 ? TRUE : FALSE);
		else if (str_eql(node->command, *(built_in_cmds + i)))
			return (TRUE);
	}
	return (FALSE);
}

/**
 * is_binary_file - checks if a file is a binary file
 * @fn: file file name
 *
 * Return: True or False
 */
char is_binary_file(char *fn)
{
	unsigned char buf[5];
	int n = 4, fd = open(fn, O_RDONLY);
	const char *s1 = (const char *) buf, *s2 = ELFMAG;

	if (fd == -1)
	{
		return (-1);
	}
	if (read(fd, buf, n) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	/*compare buf with ELFMAG*/
	for ( ; n && *s1 && *s2; --n, ++s1, ++s2)
	{
		if (*s1 != *s2)
			return (FALSE);
	}

	return (TRUE);
}

/**
 * is_variable - Checks if the given string is a variable
 * @str: The string to check
 *
 * Return: TRUE if it is a variable, otherwise FALSE
 */
char is_variable(char *str)
{
	int i = 0;

	while ((str != NULL) && (*(str + i) != '\0'))
	{
		if (is_digit(*(str + i)) && i == 0)
			break;
		else if ((is_digit(*(str + i)) && (i > 0))
			|| (is_letter(*(str + i)))
			|| (*(str + i) == '_'))
			i++;
		else
			break;
	}
	if ((str != NULL) && (*(str + i) == '\0') && (i > 0))
		return (TRUE);
	else
		return (FALSE);
}

/**
 * is_exec_file - Checks if a file is executable
 * @fp: file path
 *
 * Return: True or False
 */
char is_exec_file(char *fp)
{
	if (access(fp, F_OK | R_OK | X_OK) == 0)
		return (TRUE);
	return (FALSE);
}
