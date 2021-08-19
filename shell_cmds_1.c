#include "main.h"

/**
 * sc_history - Prints the history of this shell
 * @ac: The number of arguments passed
 * @av: The arguments passed
 *
 * Return: The function's exit code
 */
int sc_history(int ac, char *av[])
{
	int i, j, max_width, width;
	int hist_count;
	char **history = get_history(&hist_count);
	char *num;

	if (ac == 0)
	{
		max_width = str_len(long_to_str(hist_count));
		for (i = 0; i < hist_count; i++)
		{
			num = long_to_str(i);
			width = str_len(num);

			write(STDOUT_FILENO, " ", 1);
			for (j = 0; j < (max_width - width); j++)
				write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, num, width);
			write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, *(history + i), str_len(*(history + i)));
			write(STDOUT_FILENO, "\n", 1);
			free(num);
		}
	}
	(void)av;
	return (EC_SUCCESS);
}

/**
 * sc_setenv - Adds or replaces an environment variable in this shell
 * @ac: The number of arguments passed
 * @av: The arguments passed
 *
 * Return: The function's exit code
 */
int sc_setenv(int ac, char *av[])
{
	if (ac == 2)
	{
		if (is_variable(av[0]))
		{
			add_env_var(av[0], av[1]);
			return (EC_SUCCESS);
		}
		else
		{
			return (EC_GENERAL_ERROR);
		}
	}
	else
	{
		write(STDOUT_FILENO, "Invalid format\n", 15);
		return (EC_INVALID_ARGS);
	}
}

/**
 * sc_unsetenv - Removes an environment variable from this shell
 * @ac: The number of arguments passed
 * @av: The arguments passed
 *
 * Return: The function's exit code
 */
int sc_unsetenv(int ac, char *av[])
{
	if (ac == 1)
	{
		remove_env_var(av[0]);
		return (EC_SUCCESS);
	}
	else
	{
		write(STDOUT_FILENO, "Invalid format\n", 15);
		return (EC_INVALID_ARGS);
	}
}
