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

/**
 * get_variables - Retrieves an array of variables from a string
 * @str: The source string
 * @vars_count
 *
 * Return: The list of variables, otherwise NULL
*/
char **get_variables(char *str, int *vars_count)
{
	int i = 0, j, p = 0, q;
	char **vars = NULL, stop = FALSE;

	*vars_count = 0;
	while (str != NULL && *(str + i) != '\0')
	{
		if (*(str + i) == '$')
		{
			for (j = 1; !stop && *(str + i + j) != '\0'; j++)
			{
				if ((*(str + i + j) == '?') || (*(str + i + j) == '$'))
					stop = TRUE;
				else if (is_letter(*(str + i + j)) || (is_digit(*(str + i + j)) && j > 1))
					continue;
				else
					j = 0, stop = TRUE;
			}
			vars = j == 0 ? vars : _realloc(vars, sizeof(void *) * p, sizeof(void *) * (p + 1));
			if (vars != NULL && j > 0)
			{
				*(vars + p) = malloc(sizeof(char) * (j + 1));
				if (*(vars + p) != NULL)
				{
					for (q = 0; *(str + i + q) != '\0'; q++)
						*(*(vars + p) + q) = *(str + i + q);
					*(*(vars + p) + q) = '\0';
				}
				p++;
			}
		}
	}
	*vars_count = p;
	return (vars);
}

/**
 * expand_variables - Expands the variables in a node
 * @node: The node
 */
void expand_variables(cmd_t **node)
{
	int i, j, n;
	char **vars = NULL, *var_val;

	for (i = 0; i < (*node)->args_count; i++)
	{
		vars = get_variables((*node)->args[i], &n);
		if (vars != NULL)
		{
			for (j = 0; j < n; j++)
			{
				if (str_cmp("$?", *(vars + j)) == 0)
					var_val = long_to_str(*((int *)get_shell_prop(NODE_EXIT_CODE_ID)));
				else if (str_cmp("$$", *(vars + j)) == 0)
					var_val = long_to_str(*((int *)get_shell_prop(SHELL_PID_ID)));
				else
					var_val = str_copy(get_env_var(*(vars + j)));
				(*node)->args[i] = str_replace((*node)->args[i],
					*(vars + j), var_val, TRUE);
			}
		}
	}
}
