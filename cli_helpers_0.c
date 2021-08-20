#include "main.h"

/**
 * get_next_command - Gets the next command that can be executed by the shell
 * @cur: The current command node
 * @exit_code: The exit code of the last command
 *
 * Return: A pointer to the next executable command node
 */
cmd_t *get_next_command(cmd_t *cur, int exit_code)
{
	cmd_t *node = NULL;

	if (((cur->next_cond == OP_OR) && (exit_code != 0))
		|| ((cur->next_cond == OP_AND) && (exit_code == 0)))
	{
		return (cur->next);
	}
	else
	{
		node = cur;
		while (node != NULL)
		{
			if (node->next_cond == OP_SEP)
				return (node->next);
			node = node->next;
		}
		return (node);
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
 * handle_ctrl_d - Handles Control+D key press
 * @len: The number of characters on the command line
 */
void handle_ctrl_d(int len)
{
	char *buf[] = {"0"};

	if (len == 0)
		sc_exit(1, buf);
}
