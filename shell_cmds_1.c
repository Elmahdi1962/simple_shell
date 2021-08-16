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
	char **history = *((char ***)get_shell_prop(CMD_HISTORY_ID));
	int hist_count = *((int *)get_shell_prop(CMD_HISTORY_COUNT_ID));
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

int sc_setenv(int ac, char *av[])
{
	(void)ac;
	(void)av;
	return (0);
}

int sc_unsetenv(int ac, char *av[])
{
	(void)ac;
	(void)av;
	return (0);
}
