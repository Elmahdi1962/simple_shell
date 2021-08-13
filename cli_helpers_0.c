#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * get_cmd_line - Reads a line of characters from the stdin
 *
 * Return: a pointer to the string
 */
char *get_cmd_line()
{
	size_t size = 0;
	int i = 0, j, n = 0, incr = 10;
	char *buf = NULL, *line = NULL;

	buf = malloc(sizeof(char) * incr);
	if (buf != NULL)
	{
		while (TRUE)
		{
			for (j = 0; j < incr; j++)
				*(buf + j) = 0;
			n = read(STDIN_FILENO, (void *)buf, incr);
			if (buf[0] == '\n')
				break;
			for (j = 0; *(buf + j) != '\n' && j < n; j++)
				;
			line = _realloc(line, sizeof(char) * size, sizeof(char) * (size + j));
			if (line != NULL)
			{
				size += j;
				for (j = 0; *(buf + j) != '\n' && j < n; j++)
				{
					*(line + i) = *(buf + j);
					i++;
				}
				if ((j < n && *(buf + j) == '\n') || n == 0)
					break;
			}
		}
	}
	line = _realloc(line, sizeof(char) * size, sizeof(char) * (size + 1));
	*(line + size) = '\0';
	line = trim_start(line, ' ', TRUE);
	line = trim_end(line, ' ', TRUE);
	return (line);
}

/**
 * get_env_var - Retrieves the value of an environment variable
 * @var: The name of the environment variable
 *
 * Return: The pointer to the environment variable's value, otherwise, NULL
 */
char *get_env_var(char *var)
{
	char **envp = *((char ***)get_shell_prop(ENVP_ID));
	int n = *((int *)get_shell_prop(ENVP_COUNT_ID));
	int i, j;

	if (envp != NULL)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; (*(var + j) != '\0') && (*(*(envp + i) + j) != '\0'); j++)
			{
				if ((*(*(envp + i) + j) != *(var+ j)) || (*(*(envp + i) + j) == '='))
					break;
			}
			if (*(*(envp + i) + j) == '=' && *(var + j) == '\0')
			{
				return (*(envp + i) + j  + 1);
			}
		}
	}
	return (NULL);
}

/**
 * set_env_var - Sets the value of an environment variable
 * @var: The name of the environment variable
 * @val: The value of the environment variable
 */
void set_env_var(char *var, char*val)
{
	char **envp = *((char ***)get_shell_prop(ENVP_ID));
	int n = *((int *)get_shell_prop(ENVP_COUNT_ID));
	int i, j;

	if (envp != NULL)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; (*(var + j) != '\0') && (*(*(envp + i) + j) != '\0'); j++)
			{
				if ((*(*(envp + i) + j) != *(var+ j)) || (*(*(envp + i) + j) == '='))
					break;
			}
			if (*(*(envp + i) + j) == '=' && *(var + j) == '\0')
			{
				if (val != NULL)
				{
					*(envp + i) = str_cat(str_cat(var, "=", FALSE), str_copy(val), TRUE);
					break;
				}
			}
		}
	}
}


cmd_t *parse_cmd_line(char *line)
{
	int i, j, k, c = 0;
	/* size_t args_size = 0; */
	cmd_t *head = NULL, *node = NULL;
	char prev_token = 0, *word = NULL;
	/**
	 * token_types:
	 * 0 -> Beginning
	 * 1 -> word
	 * 2 -> space
	 * 3 -> operator
	 */

	if (line != NULL && *line != '\0')
	{
		for (i = 0; *(line + i) != '#' && *(line + i) != '\0'; i++)
		{
			if (is_whitespace(*(line + i)))
			{
				prev_token = 2, j = 0;
			}
			else if ((*(line + i) == '|') || ((*(line + i) == '&'))
				|| (*(line + i) == ';'))
			{
				if ((*(line + i + 1) != '\0') && (prev_token == 1 || prev_token == 2) && ((*(line + i) == ';')
						|| ((*(line + i + 1) == '|') || ((*(line + i + 1) == '&')))))
				{
					if (node != NULL)
						node->next_cond = ((*(line + i + 1) == '|') ? OR_OP
							: ((*(line + i + 1) == '&') ? AND_OP : SEP_OP));
					prev_token = 3, j = 0;
					i += ((*(line + i) == ';') ? 0 : 1);
					if (node != NULL)
						add_node_to_end(&head, &node);
				}
				else
				{
					/* Syntax error */
					printf("Syntax error\n");
				}
			}
			else if (*(line + i) == '#')
			{
				break;
			}
			else
			{
				j = prev_token != 1 ? i : j;
				if (is_whitespace(*(line + i + 1)) || is_operator(*(line + i + 1))
					|| ((*(line + i + 1) == '\0')))
				{
					word = malloc(sizeof(char) * (i - j + 2));
					if (word != NULL)
					{
						for (k = 0; k < (i - j + 1); k++)
							*(word + k) = *(line + j + k);
						*(word + k) = '\0';
						if (node == NULL)
						{
							node = new_cmd_node();
							if (node != NULL)
								node->command = word;
							c++;
						}
						else
						{
							node->args = _realloc(node->args, node->args_count * (sizeof(void *)),
								sizeof(void *) * (node->args_count + 1));
							if (node->args != NULL)
							{
								*(node->args + node->args_count) = word;
								node->args_count++;
							}
						}
					}
				}
				prev_token = 1;
			}
		}
		if (node != NULL)
			add_node_to_end(&head, &node);
	}
	return (head);
}

/* void expand_vars(cmd_t *node)
{
	int i, j, k;
	char *str;

	for (i = 0; i < node->args_count; i++)
	{
		//
	}
}
 */
