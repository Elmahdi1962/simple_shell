#include "main.h"

/**
 * exec_built_in_cmd - Executes a built-in command
 * @node: The built-in command's node
 *
 * Return: The exit code of the command
 */
int exec_built_in_cmd(cmd_t *node)
{
	int i;
	struct built_in_cmd_s built_in_cmds[] = {
		{"alias", sc_alias},
		{"cd", sc_cd},
		{"env", sc_env},
		{"exit", sc_exit},
		{"help", sc_help},
		{"history", sc_history},
		{"setenv", sc_setenv},
		{"unsetenv", sc_unsetenv}
	};

	for (i = 0; i < 8; i++)
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
	int i;

	for (i = 0; i < ac; i++)
	{

	}
	(void)av;
	return (0);
}

int sc_cd(int ac, char *av[])
{
	int i;
	char *pwd = get_env_var("PWD");
	char *old_pwd = get_env_var("OLDPWD");

	if (ac == 0)
	{
		set_env_var("OLDPWD", pwd);
		set_env_var("PWD", get_env_var("HOME"));
		chdir(get_env_var("HOME"));
	}
	else
	{
		if (str_cmp("-", av[0]) == 0)
		{
			/* Switch PWD and OLDPWD */
			if (old_pwd != NULL)
			{
				set_env_var("OLDPWD", pwd);
				set_env_var("PWD", old_pwd);
				chdir(old_pwd);
			}
			else
			{
				printf("OLDPWD not set");
				return (EC_INVALID_ARGS);
			}
		}
		else
		{
			i = chdir(av[0]);
			printf(">> %d, %d\n", i, errno);
			if (i >= 0)
			{
				set_env_var("OLDPWD", pwd);
				set_env_var("PWD", av[0]);
			}
			else
			{
				printf("can't cd to ");
				return (EC_INVALID_ARGS);
			}
		}
	}
	return (EC_SUCCESS);
}

int sc_exit(int ac, char *av[])
{
	int status = EC_SUCCESS;

	if (av == NULL)
	{
		/* TODO: Print error message */
		/* return (-1); */
	}
	if (ac > 0)
	{
		if (str_is_num(av[0]))
		{
			status = str_to_int(av[0]);
		}
		else
		{
			/* Raise error */
			return (2);
		}
	}
	save_history();
	exit(status);
	return (status);
}

/**
 * sc_env - Prints the shell's environment variables
 * @ac: The number of arguments
 * @av: The arguments
 *
 * Return: 0 if successful
 */
int sc_env(int ac, char *av[])
{
	char **envp = *((char ***)get_shell_prop(ENVP_ID));
	int n = *((int *)get_shell_prop(ENVP_COUNT_ID));
	int i;

	(void)ac;
	(void)av;
	for (i = 0; i < n; i++)
	{
		write(STDOUT_FILENO, *(envp + i), str_len(*(envp + i)));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * sc_help - Prints the help page of a built-in command
 * @ac: The number of arguments
 * @av: The arguments
 *
 * Return: 0 if successful
 */
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
	{
		help_program();
	}
	return (0);
}

/**
 * sc_history - Prints the history of this shell
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
