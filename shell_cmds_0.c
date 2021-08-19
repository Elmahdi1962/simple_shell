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
	int i, n;
	alias_t **aliases = (ac == 0 ? get_aliases(&n) : NULL);
	char *name, *value;

	if (ac <= 0)
	{
		for (i = 0; i < n; i++)
		{
			write(STDOUT_FILENO, (*(aliases + i))->name,
			str_len((*(aliases + i))->name));
			write(STDOUT_FILENO, "='", 2);
			write(STDOUT_FILENO, (*(aliases + i))->value,
			str_len((*(aliases + i))->value));
			write(STDOUT_FILENO, "'\n", 2);
		}
	}
	else
	{
		printf("-- sc_alias ac: %d\n", ac);
		for (i = 0; i < ac; i++)
		{
			if (is_variable(av[i]))
			{
				printf("(s_a): %s is a variable\n", av[i]);
				value = get_alias_value(av[i]);
				if (value != NULL)
				{
					write(STDOUT_FILENO, av[i], str_len(av[i]));
					write(STDOUT_FILENO, "='", 2);
					write(STDOUT_FILENO, value == NULL ? "" : value, str_len(value));
					write(STDOUT_FILENO, "'\n", 2);
				}
				else
				{
					write(STDERR_FILENO, "alias: ", 7);
					write(STDERR_FILENO, av[i], str_len(av[i]));
					write(STDERR_FILENO, " not found\n", 11);
					return (1);
				}
			}
			else if (is_alias_assignment(av[i], &name, &value))
			{
				printf("(s_a): name: %s, val: %s\n", name, value);
				add_alias(name, value);
			}
			else
			{
				printf("(s_a): Invalid arguments\n");
				return (EC_INVALID_ARGS);
			}
		}
	}
	return (EC_SUCCESS);
}

/**
 * sc_cd - Changes the current working directory
 * @ac: arguments count
 * @av: array of arguments
 *
 * Return: The function's exit code
 */
int sc_cd(int ac, char *av[])
{
	size_t bufsize = 1024;
	char pwd[1024];
	char *home = get_env_var("HOME");
	char *oldpwd = get_env_var("OLDPWD");

	getcwd(pwd, bufsize);
	if (ac <= 0)
	{
		set_env_var("OLDPWD", pwd);
		chdir(home);
		set_env_var("PWD", home);
	}
	else
	{
		if (str_eql(av[0], "~"))
		{
			set_env_var("OLDPWD", pwd);
			chdir(home);
			set_env_var("PWD", home);
		} else if (str_eql(av[0], "-"))
		{
			set_env_var("OLDPWD", pwd);
			chdir(oldpwd);
			set_env_var("PWD", oldpwd);
		} else
		{
			set_env_var("OLDPWD", pwd);
			if (chdir(av[0]) == 0)
			{
				set_env_var("PWD", av[0]);
			} else
				print_error("cd", av[0], "can't cd to ");
		}
	}
	return (EC_SUCCESS);
}

/**
 * sc_exit - Exits the shell with an optional status code
 * @ac: The number of arguments
 * @av: The arguments
 *
 * Return: 0 if successful
 */
int sc_exit(int ac, char *av[])
{
	char *buf0, *buf1;
	int status = *((int *)get_shell_prop(NODE_EXIT_CODE_ID));

	if (ac > 0)
	{
		if (str_is_num(av[0]))
		{
			status = str_to_int(av[0]);
		}
		else
		{
			buf0 = *((char **)get_shell_prop(EXEC_NAME_ID));
			buf1 = long_to_str(get_line_num());
			write(STDERR_FILENO, buf0, str_len(buf0));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, buf1, str_len(buf1));
			write(STDERR_FILENO, ": exit: ", 8);
			write(STDERR_FILENO, "Illegal number: ", 16);
			write(STDERR_FILENO, av[0], str_len(av[0]));
			write(STDERR_FILENO, "\n", 1);
			free(buf1);
			return (2);
		}
	}
	clean_up_shell();
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
		{"history", help_history},
		{"setenv", help_setenv},
		{"unsetenv", help_unsetenv}
	};

	if (ac > 0)
	{
		for (i = 0; i < 9; i++)
		{
			if (str_eql(cmds_help[i].cmd_name, av[0]))
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
