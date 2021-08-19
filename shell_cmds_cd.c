#include "main.h"

/* TODO: Fix this algorithm and handle errors */
int sc_cd(int ac, char *av[])
{
	int i;
	char *pwd = get_env_var("PWD"), *new_path = NULL, error = EC_SUCCESS;
	char *old_pwd = get_env_var("OLDPWD");

	if (ac <= 0)
	{
		set_env_var("OLDPWD", pwd), set_env_var("PWD", get_env_var("HOME"));
		chdir(get_env_var("HOME"));
	}
	else
	{
		if (str_eql("-", av[0]))
		{
			change_to_old_pwd(pwd, old_pwd, &error);
		}
		else
		{
			new_path = resolve_path(pwd, av[0], &error);
			i = chdir(new_path);
			/* printf(">> %d, %d, -> %s\n", i, errno, new_path); */
			if ((error == FALSE) && (i >= 0))
			{
				set_env_var("OLDPWD", pwd);
				set_env_var("PWD", new_path);
			}
			else
			{
				print_failed_dir_nav_error(av[0], error);
			}
			if (new_path != NULL)
				free(new_path);
		}
	}
	return (error);
}

void change_to_old_pwd(char *pwd, char *old_pwd, char *error)
{
	DIR *old_dir;
	char *buf0, *buf1;

	if (old_pwd != NULL)
	{
		old_dir = opendir(old_pwd);
		if ((old_dir != NULL) && (chdir(old_pwd) >= 0))
		{
			closedir(old_dir);
			set_env_var("OLDPWD", pwd);
			set_env_var("PWD", old_pwd);
			write(STDOUT_FILENO, old_pwd, str_len(old_pwd));
			write(STDERR_FILENO, "\n", 1);
		}
		else
		{
			buf0 = *((char **)get_shell_prop(EXEC_NAME_ID));
			buf1 = long_to_str(get_line_num());
			write(STDERR_FILENO, buf0, str_len(buf0));
			write(STDERR_FILENO, ": ", 15);
			write(STDERR_FILENO, buf1, str_len(buf1));
			write(STDERR_FILENO, ": cd: Permission denied\n", 25);
			*error = EC_CANNOT_EXECUTE;
		}
	}
	else
	{
		write(STDERR_FILENO, "OLDPWD not set\n", 15);
		*error = EC_INVALID_ARGS;
	}
}

/**
 * resolve_path - Resolves a given path to the absolute path based
 * on the current working directory
 * @cwd: The current working directory
 * @path: The path to resolve
 * @error: A pointer to the error flag
 *
 * Return: The resolved path, otherwise NULL
 */
char *resolve_path(char *cwd, char *path, char *error)
{
	char *res = NULL, **res_dirs, **in_dirs;
	int res_dirs_count = 0, in_dirs_count = 0, i;

	res_dirs = str_split(cwd, '/', &res_dirs_count, FALSE);
	in_dirs = str_split(path, '/', &in_dirs_count, FALSE);
	for (i = 0; i < in_dirs_count; i++)
	{
		if (str_eql(*(in_dirs + i), ".."))
		{
			if (res_dirs_count > 0)
			{
				free(*(res_dirs + res_dirs_count));
				res_dirs_count--;
			}
			else
			{
				(*error)++;
			}
		}
		else if (str_len(*(in_dirs + i)) == 0)
		{
		}
		else if (str_eql(*(in_dirs + i), ".") == FALSE)
		{
			res_dirs = _realloc(res_dirs, sizeof(void *) * res_dirs_count,
				sizeof(void *) * (res_dirs_count + 1));
			if (res_dirs != NULL)
			{
				*(res_dirs + res_dirs_count) = str_copy(*(in_dirs + i));
				res_dirs_count++;
			}
		}
	}
	free_array(in_dirs, in_dirs_count);
	res = strs_join(res_dirs, res_dirs_count, '/', TRUE);
	return (res);
}

void print_failed_dir_nav_error(char *path, char error)
{
	char *buf0, *buf1;

	buf0 = *((char **)get_shell_prop(EXEC_NAME_ID));
	buf1 = long_to_str(get_line_num());
	/* if (!error) */
		/* write(STDERR_FILENO, "-", 1); */
	write(STDERR_FILENO, buf0, str_len(buf0));
	if (error)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, buf1, str_len(buf1));
	}
	write(STDERR_FILENO, ": cd: ", 6);
	if (error)
		write(STDERR_FILENO, "can't cd to ", 13);
	write(STDERR_FILENO, path, str_len(path));
	if (error)
		write(STDERR_FILENO, "\n", 1);
	else
		write(STDERR_FILENO, ": No such file or directory\n", 28);
}
