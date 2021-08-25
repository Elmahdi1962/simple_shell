#include "main.h"

/**
 * check_path - Checks if a given file command exists
 * @str: File name, which could include ./ like "./program"
 *
 * Return: The full path of a non-built-in command or NULL
 */
char *check_path(char *str)
{
	char *file_path = str_copy(str), *full_path = NULL;
	int fd;

	if (*str == '.' || *str == '/')
	{
		fd = open(file_path, O_RDONLY);
		if (fd >= 0)
		{
			close(fd);
			if (is_exec_file(file_path) && is_regular_file(file_path))
			{
				free(file_path);
				return (str);
			}
			free(file_path);
			return (NULL);
		}
		free(file_path);
		return (NULL);
	}

	/**
	 * the file path doesn't start with . or /
	 * Checking if it's one of the built out commands programs in
	 * one of the paths in PATH
	 */
	full_path = search_path(file_path);
	free(file_path);
	return (full_path);
}

/**
 * search_path - Searches in PATH paths for the program of the command passed
 * @command: The name of the command
 *
 * Return: The full path of the command or NULL
 */
char *search_path(char *command)
{
	int fd, len = 0, length;
	char *path = get_env_var("PATH");
	char **paths = str_split(path, ':', &len, FALSE), *full_path, *tmp_path;

	if (path == NULL || paths == NULL)
	{
		return (NULL);
	}
	length = len;
	for (; len > 0; len--)
	{
		full_path = str_cat(paths[len - 1], "/", FALSE);
		tmp_path = full_path;
		full_path = str_cat(tmp_path, command, FALSE);
		free(tmp_path);

		fd = open(full_path, O_RDONLY);
		if (fd > 0)
		{
			free_array(paths, length);
			close(fd);
			return (full_path);
		}
		free(full_path);
	}
	free_array(paths, length);
	return (NULL);
}

/**
 * is_system_command - Checks if a command is a system command
 * @command: The command to check
 * @abs_path: A pointer to the location of the resolved path
 *
 * Return: TRUE if the command can be found, otherwise FALSE
 */
char is_system_command(char *command, char **abs_path)
{
	char *tmp0 = NULL, *tmp1 = NULL, *path = NULL, **path_dirs = NULL;
	struct stat path_stat;
	int path_dirs_count = 0, i;

	if (abs_path == NULL)
		return (FALSE);
	*abs_path = NULL;
	if (contains_char(command, '/'))
	{
		stat(command, &path_stat);
		if ((access(command, R_OK | F_OK | X_OK) == 0)
			&& (S_ISREG(path_stat.st_mode)))
		{
			*abs_path = str_copy(command);
			return (TRUE);
		}
	}
	else
	{
		path = get_env_var("PATH");
		if (path && (path != NULL))
		{
			path_dirs = str_split(path, ':', &path_dirs_count, FALSE);
			for (i = 0; i < path_dirs_count; i++)
			{
				tmp0 = str_cat(*(path_dirs + i), "/", FALSE);
				tmp1 = str_cat(tmp0, command, FALSE), stat(tmp1, &path_stat);
				if ((access(tmp1, R_OK | F_OK | X_OK) == 0) &&
				(S_ISREG(path_stat.st_mode)))
				{
					free_array(path_dirs, path_dirs_count), *abs_path = tmp1, free(tmp0);
					return (TRUE);
				}
				free(tmp0), free(tmp1), tmp0 = NULL, tmp1 = NULL;
			}
			free_array(path_dirs, path_dirs_count);
		}
	}
	return (FALSE);
}
