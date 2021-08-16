#include "main.h"

/**
 * read_all_lines - Reads all the lines in a text file
 * @file_name: The path to the file
 * @flags: The flags to use when reading the file
 * @lines: A pointer to the lines in the file
 *
 * return: A 2D array of the files contents, otherwise NULL
 */
char **read_all_lines(char *file, int flags, int *lines)
{
	int j, n, fd, buf_size = 126;
	char *buf = NULL;
	char *str = NULL;

	if (file == NULL)
		return (NULL);
	fd = open(file, flags);
	if (fd >= 0)
	{
		buf = malloc(sizeof(char) * (buf_size + 1));
		if (buf != NULL)
		{
			while (1 && buf != NULL)
			{
				for (j = 0; j <= buf_size; j++)
					buf[j] = 0;
				n = read(fd, (void *)buf, buf_size);
				if (n == 0)
					break;
				buf[n] = '\0';
				str = str_cat(str, buf, TRUE);
				buf = malloc(sizeof(char) * (buf_size + 1));
			}
		}
		if (buf != NULL)
			free(buf);
		close(fd);
	}
	return (str_split(str, '\n', lines, TRUE));
}

/**
 * print_text - Writes an array of strings to a file handle
 * @fd: The file handle to write to
 * @text: The array of strings to write
 * @n: The number of items in the array of strings
 */
void print_text(int fd, char *text[], int n)
{
	int i;

	for (i = 0; i < n; i++)
		write(fd, text[i], str_len(text[i]));
}
