#include "main.h"
#include <stdlib.h>

/**
 * check_path - checks if the file exists
 * @str: file name it could enclude ./ like "./program"
 * Return: full path or NULL
 */

char *check_path(char *str)
{
	char *pwd = get_env_var("PWD"), *full_path, *file_path = str;
	int fd;

	if (*str == '.')
	{
		full_path = str_cat(pwd, file_path, FALSE);
		fd = open(full_path, O_RDONLY);
		if (fd >= 0)
		{
			close(fd);
			if (is_exec_file("test"))
			{
				return(full_path);
			}
			perror("file is not executable\n");
			return(NULL);
		}
		return (NULL);
	}
	if (*str == '/')
	{
		full_path = file_path;
		fd = open(full_path, O_RDONLY);
		if (fd >= 0)
		{
			close(fd);
			if (is_exec_file(full_path))
			{
				return(full_path);
			}
			perror("file is not executable\n");
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
	int fd, len;
	char *pwd = get_env_var("PWD");
	char **paths = str_split(pwd, ':', &len, FALSE), *full_path;

	for (;len > 0; len--)
	{
		full_path = str_cat(paths[len - 1], command, TRUE);
		fd = open(full_path, O_RDONLY);
		if (fd >0)
		{
			free(paths);
			return (full_path);
		}
		close(fd);
	}
	free(paths);
	return (NULL);
}
