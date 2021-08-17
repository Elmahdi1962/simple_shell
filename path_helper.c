#include "main.h"

/**
 * check_path - checks if the file exists
 * @str: file name it could enclude ./ like "./program"
 *
 * Return: full path or NULL
 * NOTE : IF THIS FUNCTION RETURNED A PATH (NOT NULL) THEN YOU NEED TO FREE THAT VARIABLE
 * AFTER FINISHING USING IT
 */
char *check_path(char *str)
{
	char *file_path = str, *full_path;
	int fd;

	if (*str == '.' || *str == '/')
	{
		fd = open(file_path, O_RDONLY);
		if (fd >= 0)
		{
			close(fd);

			if (is_exec_file(file_path) && is_regular_file(file_path))
			{
				return(file_path);
			}

			return(NULL);
		}
		return (NULL);
	}

	/*the file path doesn't start with . or / */
	/*Checking if it's one of the built out commands programs in one of the paths in PATH*/
	full_path = search_path(file_path);

	return (full_path);
}

/**
 * search_path - search in PATH paths for the program of the command passed
 * @command: command name
 * Return: full path or NULL
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
	for (;len > 0; len--)
	{
		full_path = str_cat(paths[len - 1], "/", FALSE);
		tmp_path = full_path;
		full_path = str_cat(tmp_path, command, FALSE);
		free(tmp_path);

		fd = open(full_path, O_RDONLY);
		if (fd >0)
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
