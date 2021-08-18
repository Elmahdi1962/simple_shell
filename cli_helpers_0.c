#include "main.h"

/**
 * get_cmd_line - Reads a line of characters from the stdin
 *
 * Return: a pointer to the string
 */
char *get_cmd_line()
{
	size_t size = 0;
	int i = 0, j, k, n = 0, incr = 1024, quote_o = 0;
	char *line = NULL, q_a = 0;
	static char buf[1024];

	mem_set(buf, incr, '\0');
	while (TRUE && (n = read(STDIN_FILENO, (void *)buf, incr)))
	{
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
					q_a = buf[j];
					quote_o = 1;
				}
				else if ((*(buf + j) == q_a))
				{
					q_a = 0;
					quote_o = 0;
				}
			}
			if ((buf[j] == '\n') && (quote_o == 1))
				write(STDOUT_FILENO, "> ", 2), fflush(stdout);
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
			if (((j <= n) && (*(buf + j) == '\n') && (quote_o == 0)) || (n == 0))
				break;
		}
		mem_set(buf, incr, '\0');
	}

	if ((n == 0) && !((quote_o == 0) && (*(buf + j) == '\n')))
	{
		perror("Syntax error\n");
		free(line);
		return (NULL);
	}
	line = _realloc(line, sizeof(char) * size, sizeof(char) * (size + 1));
	*(line + size) = '\0';
	return (line);
}

/**
 * get_next_command - Gets the next command that can be executed by the shell
 * @cur: The current command node
 * @exit_code: The exit code of the last command
 *
 * Return: A pointer to the next executable command node
 */
cmd_t *get_next_command(cmd_t *cur, int exit_code)
{
	cmd_t *node;

	if (((cur->next_cond == OP_OR) && (exit_code != 0))
		|| ((cur->next_cond == OP_AND) && (exit_code == 0)))
	{
		return (cur->next);
	}
	else
	{
		node = cur;
		while (node->next != NULL)
		{
			if (node->next_cond == OP_SEP)
				return (node->next);
			node = node->next;
		}
		return (NULL);
	}
}

/**
 * get_variables - Retrieves an array of variables from a string
 * @str: The source string
 * @vars_count: count of vars
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

/**
 * print_prompt - Prints the prompt for this shell program
 */
void print_prompt(void)
{
	char *ps1 = get_env_var("PS1");
	int j, n;
	char **vars = NULL, *var_val = NULL;

	if (ps1 == NULL)
		ps1 = str_copy("$ ");
	else
		ps1 = str_copy(ps1);
	vars = get_variables(ps1, &n);
	if (vars != NULL)
	{
		for (j = 0; j < n; j++)
		{
			if (str_eql("$?", *(vars + j)))
				var_val = long_to_str(*((int *)get_shell_prop(NODE_EXIT_CODE_ID)));
			else if (str_eql("$$", *(vars + j)))
				var_val = long_to_str(*((int *)get_shell_prop(SHELL_PID_ID)));
			else
				var_val = str_copy(get_env_var(*(vars + j) + 1));
			ps1 = str_replace(ps1, *(vars + j), var_val, TRUE);
		}
		free(vars);
	}
	write(STDOUT_FILENO, ps1, str_len(ps1));
	free(ps1);
}
