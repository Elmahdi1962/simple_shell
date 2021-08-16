#include "main.h"

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
