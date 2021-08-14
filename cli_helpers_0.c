#include "main.h"

/**
 * get_cmd_line - Reads a line of characters from the stdin
 *
 * Return: a pointer to the string
 */
char *get_cmd_line()
{
	size_t size = 0;
	int i = 0, j, k, n = 0, incr = 10, quote_d = 0;
	char *buf = NULL, *line = NULL, q_a = 0;

	buf = malloc(sizeof(char) * incr);
	if (buf != NULL)
	{
		while (TRUE)
		{
			for (j = 0; j < incr; j++)
				*(buf + j) = 0;
			n = read(STDIN_FILENO, (void *)buf, incr);
			if (n < 0)
				return (NULL);
			if (buf[0] == '\n' && quote_d == 0)
				break;
			for (j = 0; !((quote_d == 0) && (*(buf + j) == '\n')) && (j < n); j++)
			{
				if (is_quote(*(buf + j)))
				{
					if (q_a == 0)
					{
						q_a = *(buf + j);
						quote_d = 1;
					}
					else if ((*(buf + j) == q_a))
					{
						q_a = 0;
						quote_d = 0;
					}
				}
			}
			line = _realloc(line, sizeof(char) * size, sizeof(char) * (size + j));
			if (line != NULL)
			{
				size += j;
				for (k = 0; k < j; k++)
				{
					*(line + i) = *(buf + k);
					i++;
				}
				if ((j <= n && *(buf + j) == '\n' && quote_d == 0) || n == 0)
					break;
			}
		}
	}
	if (n == 0 && !((quote_d == 0) && (*(buf + j) == '\n')))
	{
		perror("Syntax error\n");
		free(line), free(buf);
		return (NULL);
	}
	line = _realloc(line, sizeof(char) * size, sizeof(char) * (size + 1));
	*(line + size) = '\0';
	return (line);
}

char **get_variables(char *str, int *vars_count)
{
	int i = 0, j;
	char **vars = NULL;

	*vars_count = 0;
	while (str != NULL && *(str + i) != '\0')
	{
		if (*(str + i) == '$')
		{
			//
		}
	}
	return (vars);
}
