#include "main.h"

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
	char *home = get_env_var("HOME"), *home_copy;
	char *oldpwd = get_env_var("OLDPWD"), *oldpwd_copy;

	getcwd(pwd, bufsize);
	if (ac <= 0 || str_eql(av[0], "~"))
	{
		home_copy = str_copy(home);
		set_env_var("OLDPWD", pwd);
		chdir(home_copy);
		set_env_var("PWD", home_copy);
		free(home_copy);
	}
	else
	{
		if (str_eql(av[0], "-"))
		{
			oldpwd_copy = str_copy(oldpwd);
			set_env_var("OLDPWD", pwd);
			chdir(oldpwd_copy);
			set_env_var("PWD", oldpwd_copy);
			write(STDOUT_FILENO, oldpwd_copy, str_len(oldpwd_copy));
			write(STDOUT_FILENO, "\n", 1);
			free(oldpwd_copy);
		} else
		{
			set_env_var("OLDPWD", pwd);
			if (chdir(av[0]) == 0)
			{
				getcwd(pwd, bufsize);
				set_env_var("PWD", pwd);
			} else
			{
				print_error("cd", av[0], "can't cd to ");
				return (errno);
			}
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
			return (EC_INVALID_ARGS);
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
	return (EC_SUCCESS);
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
	cmd_help_t cmds_help[] = {
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
				return (EC_SUCCESS);
			}
		}
	}
	else
	{
		help_program();
	}
	return (EC_SUCCESS);
}
