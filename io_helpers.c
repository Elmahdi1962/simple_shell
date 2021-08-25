#include "main.h"

/**
 * read_all_lines - Reads all the lines in a text file
 * @fd: The file's handle
 * @lines_out: A pointer to the lines in the file
 *
 * Return: A 2D array of the file's contents, otherwise NULL
 */
char **read_all_lines(int fd, int *lines_out)
{
	int n = 0, buf_size = 1 << 7;
	char *buf = NULL;
	char *str = NULL;

	if (fd < 0)
		return (NULL);
	if (fd >= 0)
	{
		buf = malloc(sizeof(char) * (buf_size + 1));
		if (buf != NULL)
		{
			while (1 && (buf != NULL))
			{
				mem_set(buf, buf_size, '\0');
				n = read(fd, (void *)buf, buf_size);
				if (n <= 0)
					break;
				buf[n] = '\0';
				str = str_cat(str, buf, TRUE);
				buf = malloc(sizeof(char) * (buf_size + 1));
			}
		}
		if (buf != NULL)
			free(buf);
	}
	return (str_split(str, '\n', lines_out, TRUE));
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
