#include "main.h"

/**
 * sc_alias - Creates an alias for a command string, prints all the \
 * defined aliases or the value of a single alias
 * @ac: The number of arguments passed
 * @av: The arguments passed
 *
 * Return: The function's exit code
 */
int sc_alias(int ac, char *av[])
{
	int i, n, exit_code = EC_SUCCESS;
	alias_t **aliases = (ac == 0 ? get_aliases(&n) : NULL);
	char *name = NULL, *value = NULL;

	if (ac <= 0)
	{
		for (i = 0; i < n; i++)
			print_alias((*(aliases + i))->name, (*(aliases + i))->value);
	}
	else
	{
		for (i = 0; i < ac; i++)
		{
			if (is_alias_name(av[i]))
			{
				print_alias(av[i], get_alias_value(av[i]));
				if (!is_alias(av[i]))
					exit_code = EC_GENERAL_ERROR;
			}
			else if (is_alias_assignment(av[i], &name, &value))
			{
				add_alias(name, value);
				if (name != NULL)
					free(name);
				if (value != NULL)
					free(value);
				name = NULL;
				value = NULL;
			}
			else
			{
				exit_code = EC_GENERAL_ERROR;
			}
		}
	}
	return (exit_code);
}

/**
 * print_alias - Prints the name and value of an alias
 * @name: The name of the alias
 * @value: The value of the alias
 */
void print_alias(char *name, char *value)
{
	if (value != NULL)
	{
		write(STDOUT_FILENO, name, str_len(name));
		write(STDOUT_FILENO, "='", 2);
		write(STDOUT_FILENO, value, str_len(value));
		write(STDOUT_FILENO, "'\n", 2);
	}
	else
	{
		write(STDERR_FILENO, "alias: ", 7);
		write(STDERR_FILENO, name, str_len(name));
		write(STDERR_FILENO, " not found\n", 11);
	}
}
