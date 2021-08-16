#include "main.h"

/**
 * is_alias - Checks if the given string is an alias
 * @str: The string to check
 *
 * Return: TRUE or FALSE
 */
char is_alias(char *str)
{
	int n = 0;
	alias_t **aliases = get_aliases(&n);
	int i;

	if (aliases != NULL)
	{
		for (i = 0; i < n; i++)
		{
			if (str_cmp(str, (*(aliases + i))->name) == 0)
				return (TRUE);
		}
	}
	return (FALSE);
}

/**
 * is_regular_file - check if the path is a file or a directory
 * @path: file or folder path
 * Return: 1 if is a regular file 0 if not
 */

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}
