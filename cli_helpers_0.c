#include "main.h"

/**
 * get_cmd_line - Reads a line of characters from the stdin
 *
 * Return: a pointer to the string
 */
char *get_cmd_line()
{
	size_t size = 0;
	int i = 0, j, k, n = 0, incr = 10, quote_o = 0;
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
			if (buf[0] == '\n' && quote_o == 0)
				break;
			for (j = 0; !((quote_o == 0) && (*(buf + j) == '\n')) && (j < n); j++)
			{
				if (is_quote(*(buf + j)))
				{
					if (q_a == 0)
					{
						q_a = *(buf + j);
						quote_o = 1;
					}
					else if ((*(buf + j) == q_a))
					{
						q_a = 0;
						quote_o = 0;
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
				if ((j <= n && *(buf + j) == '\n' && quote_o == 0) || n == 0)
					break;
			}
		}
	}
	if (n == 0 && !((quote_o == 0) && (*(buf + j) == '\n')))
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


/**
 * get_variables - Retrieves an array of variables from a string
 * @str: The source string
 * @vars_count
 *
 * Return: The list of variables, otherwise NULL
*/
char **get_variables(char *str, int *vars_count)
{
	int i = 0, p = 0;
	char **vars = NULL, *tmp;

	*vars_count = 0;
	while ((str != NULL) && (*(str + i) != '\0'))
	{
		if (*(str + i) == '$')
		{
			tmp = read_variable(str, i + 1);
			printf("[%d](e_v): %d, %s\n", p, str_len(tmp), tmp);
			if (tmp != NULL)
			{
				vars = _realloc(vars, sizeof(void *) * p, sizeof(void *) * (p + 1));
				*(vars + p) = str_cat(str_copy("$"), tmp, TRUE);
				p++;
				i += (str_len(tmp));
			}
			else
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	*vars_count = p;
	return (vars);
}

void print_prompt()
{
	char *ps1 = get_env_var("PS1");
	int j, n;
	char **vars = NULL, *var_val;
	
	vars = get_variables(ps1, &n);
	printf("[] (p_p): %s\n", ps1);
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
			ps1 = str_replace(ps1, *(vars + j), var_val, TRUE);
		}
	}
	write(STDOUT_FILENO, ps1, str_len(ps1));
}
