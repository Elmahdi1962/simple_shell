#include <stdlib.h>
#include "main.h"

int exec_built_in_cmd(cmd_t *node)
{
	int i;
	struct built_in_cmd built_in_cmds[] = {
		{"alias", sc_alias},
		{"cd", sc_cd},
		{"env", sc_env},
		{"exit", sc_exit},
		{"help", sc_help},
		{"history", sc_history},
		{"setenv", sc_setenv},
		{"unsetenv", sc_unsetenv}
	};

	for (i = 0; i < 9; i++)
	{
		if (str_cmp(built_in_cmds[i].cmd_name, node->command) == 0)
		{
			return (built_in_cmds[i].run(node->args_count, node->args));
		}
	}
	return (0);
}

int sc_alias(int ac, char *av[])
{
	(void)ac;
	(void)av;
	return (0);
}

int sc_cd(int ac, char *av[])
{
	(void)ac;
	(void)av;
	return (0);
}

int sc_exit(int ac, char *av[])
{
	int status = 0;

	if (av == NULL)
	{
		/* TODO: Print error message */
		/* return (-1); */
	}
	if (ac >= 1)
	{
		;
	}
	/* write history to file */
	exit(status);
	return (0);
}

int sc_env(int ac, char *av[])
{
	(void)ac;
	(void)av;
	return (0);
}

int sc_help(int ac, char *av[])
{
	int i;
	struct cmd_help cmds_help[] = {
		{"alias", help_alias},
		{"cd", help_cd},
		{"exit", help_exit},
		{"help", help_help},
		{"history", help_history}
	};

	if (ac > 0)
	{
		for (i = 0; i < 9; i++)
		{
			if (str_cmp(cmds_help[i].cmd_name, av[0]) == 0)
			{
				cmds_help[i].run();
				return (0);
			}
		}
	}
	else
		help_program();

	return (0);
}

int sc_history(int ac, char *av[])
{
	(void)ac;
	(void)av;
	return (0);
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
