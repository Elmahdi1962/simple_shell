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
	int status = EC_SUCCESS;
	char pwd[PATH_MAX], *home = get_env_var("HOME");
	char *oldpwd = get_env_var("OLDPWD");

	getcwd(pwd, PATH_MAX);
	if (ac <= 0)
	{
		switch_dirs(home, pwd, &status);
	}
	else if (str_eql(av[0], "-"))
	{
		if (oldpwd != NULL)
		{
			if (switch_dirs(oldpwd, pwd, &status) == TRUE)
			{
				getcwd(pwd, PATH_MAX);
				write(STDOUT_FILENO, pwd, str_len(pwd));
				write(STDOUT_FILENO, "\n", 1);
			}
		}
		else
		{
			getcwd(pwd, PATH_MAX);
			write(STDOUT_FILENO, pwd, str_len(pwd));
			write(STDOUT_FILENO, "\n", 1);
			add_env_var("PWD", pwd), add_env_var("OLDPWD", pwd);
		}
	}
	else
	{
		switch_dirs(av[0], pwd, &status);
	}
	return (status);
}

/**
 * switch_dirs - Switches to a directory
 * @new_dir: The directory to switch to
 * @pwd: The current working directory
 * @status: The pointer to the status code
 *
 * Return: TRUE if the switch was successful, otherwise FALSE
 */
char switch_dirs(char *new_dir, char *pwd, int *status)
{
	char buf0[PATH_MAX];
	struct stat sb;

	if (new_dir != NULL)
	{
		if (stat(new_dir, &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			if (chdir(new_dir) == 0)
			{
				add_env_var("OLDPWD", pwd);
				if (getcwd(buf0, PATH_MAX) != NULL)
					add_env_var("PWD", buf0);
				return (TRUE);
			}
			else
			{
				print_error("cd", new_dir, "can't cd to ");
				*status = EC_INVALID_ARGS;
			}
		}
		else
		{
			print_error("cd", new_dir, "can't cd to ");
			*status = EC_INVALID_ARGS;
		}
	}
	return (FALSE);
}
