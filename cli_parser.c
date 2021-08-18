#include "main.h"

/**
 * parse_cmd_line - Processes a line of command into a list of command nodes
 * @line: The line of commands
 *
 * Return: The list of command nodes
 */
cmd_t *parse_cmd_line(char *line)
{
	int i = 0;
	cmd_t *head = NULL, *node = NULL;
	char prev_token = TKN_BEG, *word, *error = NULL;

	if (line != NULL && *line != '\0')
	{
		for (i = 0; *(line + i) != '#' && *(line + i) != '\0' && error == NULL;)
		{
			if (is_whitespace(*(line + i)))
			{
				prev_token = TKN_SPACE, i++;
			}
			else if (is_operator(*(line + i)))
			{
				read_operator(line, &i, prev_token, &node, &head, &error);
				prev_token = TKN_OP;
			}
			else
			{
				word = read_word(line, &i);
				insert_word(&line, &word, &node, &i);
				prev_token = TKN_WORD;
			}
		}
		if (node != NULL)
			add_node_to_end(&head, &node);
	}
	return (head);
}

void insert_word(char **str, char **word, cmd_t **node, int *pos)
{
	char *tmp;

	if (node != NULL)
	{
		if (word != NULL)
		{
			if (*node == NULL)
			{
				if (is_alias_name(*word) && is_alias(*word))
				{
					tmp = get_alias_value(*word);
					(void)tmp;
					(void)pos;
					(void)str;
					/* rep_range(*str, str_len(word), *i - str_len(word), *i); */
				}
				else
				{
					*node = new_cmd_node();
					if (*node != NULL)
					{
						(*node)->command = *word;
					}
				}
			}
			else
			{
				(*node)->args = _realloc((*node)->args, (*node)->args_count * (sizeof(void *)),
															sizeof(void *) * ((*node)->args_count + 1));
				if ((*node)->args != NULL)
				{
					*((*node)->args + (*node)->args_count) = *word;
					(*node)->args_count++;
				}
			}
		}
	}
}

void read_operator(char *line, int *pos, char prev_token,
	cmd_t **head, cmd_t **node, char **error)
{
	int i = *pos, j, op_len = 0;
	char *op_s, op = 0;

	for (j = 0; *(line + i) != '\0' && is_operator(*(line + i)); i++)
	{
		op = op == 0 ? *(line + i) : op;
		if (op != 0 && (*(line + i) != op))
			break;
		j++;
	}
	op_s = j > 0 ? malloc(sizeof(char) * (j + 1)) : NULL;
	i -= j;
	if (op_s != NULL)
	{
		for (j = 0; *(line + i) != '\0' && is_operator(*(line + i)); i++)
			*(op_s + j) = *(line + i), j++;
		*(op_s + j) = '\0', op_len = str_len(op_s);
	}
	if ((op_s != NULL)
		&& ((str_eql(";", op_s))
		|| (str_eql("||", op_s))
		|| (str_eql("&&", op_s))))
	{
		if (node != NULL && *node != NULL)
			(*node)->next_cond = ((*op_s == '|') ? OP_OR
													: ((*op_s == '&') ? OP_AND : OP_SEP));
		if (node != NULL && *node != NULL)
			add_node_to_end(head, node);
	}
	else
	{
		if (((prev_token == TKN_WORD) || (prev_token == TKN_SPACE)))
		{
			*error = str_copy("syntax error near unexpected token '");
		}
		else
		{
			*error = str_copy("syntax error near unexpected token '");
		}
	}
	(void)op_len;
	*pos = i;
}

/**
 * read_word - Reads a word from the given line
 * @line: The line to read from
 * @pos: The position in the line to start from
 *
 * Return: The word, otherwise NULL
 */
char *read_word(char *line, int *pos)
{
	int i = *pos, j = *pos, k = 0, quote_o = 0, len = 0;
	char quote = 0, *word;

	while (*(line + i) != '\0')
	{
		if (is_quote(*(line + i)))
		{
			if (quote == 0)
				quote = *(line + i), quote_o = 1;
			else if ((*(line + i) == quote))
				quote = 0, quote_o = 0;
		}
		else if (quote_o == 0)
		{
			if (is_operator(*(line + i)) || (is_whitespace(*(line + i))))
				break;
		}
		i++, len++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (word != NULL)
	{
		for (k = 0; k < len; k++)
			*(word + k) = *(line + j), j++;
		*(word + k) = '\0';
	}
	*pos = i;
	return (word);
}

/**
 * read_variable - Reads a variable from the given string
 * @str: The string to read from
 * @pos: The position in the string to start from
 *
 * Return: The variable, otherwise NULL
 */
char *read_variable(char *str, int pos)
{
	int i = pos, j, len;
	char *var = NULL;

	while (*(str + i) != '\0')
	{
		if (((*(str + i) == '$') && (i == pos))
			|| ((*(str + i) == '?') && (i == pos)))
		{
			i++;
			break;
		}
		else if ((is_digit(*(str + i)) && (i > pos))
			|| (is_letter(*(str + i)))
			|| (*(str + i) == '_'))
			i++;
		else
			break;
	}
	len = i - pos;
	var = len > 0 ? malloc(sizeof(char) * (len + 1)) : NULL;
	if (var != NULL)
	{
		for (j = 0, i = pos; j < len; j++, i++)
			*(var + j) = *(str + i);
		*(var + j) = '\0';
	}
	return (var);
}

/**
 * dissolve_tokens - Performs a context-aware dissolution of tokens
 * @str: The source string
 * @can_free: Specifies if the given string can be freed
 *
 * Return: The dissolved string, otherwise NULL
 */
char *dissolve_tokens(char *str, char can_free)
{
	size_t size = 0;
	const char incr = 0x40;
	size_t i = 0, j = 0, k, var_len = 0, val_len = 0, tmp_len;
	char *tmp;
	char *res = NULL, *var = NULL, *val = NULL, quote = FALSE, quote_o = FALSE;

	for (i = 0; *(str + i) != '\0';)
	{
		if (j >= size)
		{
			res = _realloc(res, sizeof(char) * size, sizeof(char) * (size + incr));
			size += incr;
		}
		if (((*(str + i) == '~') && (i == 0)) && ((*(str + 1) == '/') || (*(str + 1) == ':')))
		{
			tmp = str_copy(get_env_var("HOME"));
			tmp_len = str_len(tmp);
			if (tmp != NULL)
			{
				if ((j + tmp_len) > size)
				{
					/* allocate space for extra data */
					res = _realloc(res, sizeof(char) * size,
						sizeof(char) * (size + (j + tmp_len - size)));
					size += (j + tmp_len - size);
				}
				for (k = 0; k < tmp_len; k++)
				{
					*(res + j) = *(tmp + k);
					j++;
				}
				i += 2;
				free(tmp);
				tmp = NULL;
			}
		}
		else if (is_quote(*(str + i)))
		{
			if (quote == FALSE)
			{
				quote = *(str + i);
				quote_o = TRUE;
				i++;
				/* add to deletion */
			}
			else if ((*(str + i) == quote))
			{
				quote = FALSE;
				quote_o = FALSE;
				i++;
				/* add to deletion */
			}
			else
			{
				*(res + j) = *(str + i);
				j++;
				i++;
			}
		}
		else if (*(str + i) == '$')
		{
			if (((quote == '"') && (quote_o == TRUE)) || (quote_o == FALSE))
			{
				var = read_variable(str, i + 1);
				if (str_eql("?", var))
					val = long_to_str(*((int *)get_shell_prop(NODE_EXIT_CODE_ID)));
				else if (str_eql("$", var))
					val = long_to_str(*((int *)get_shell_prop(SHELL_PID_ID)));
				else if (var != NULL)
					val = str_copy(get_env_var(var));
				if (val == NULL)
				{
					*(res + j) = '$';
					j++;
					i++;
				}
				else
				{
					printf("(d_t): %s\n", val);
					/* insert variable */
					var_len = str_len(var) + 1;
					val_len = str_len(val);
					if ((j + val_len) > size)
					{
						/* allocate space for extra data */
						res = _realloc(res, sizeof(char) * size,
							sizeof(char) * (size + (j + val_len - size)));
					}
					for (k = 0; k < val_len; k++)
					{
						*(res + j) = *(val + k);
						j++;
					}
					i += var_len;
					free(val);
					val = NULL;
				}
				if (var != NULL)
					free(var);
			}
			else
			{
				*(res + j) = '$';
				j++;
				i++;
			}
		}
		else
		{
			*(res + j) = *(str + i);
			j++;
			i++;
		}
	}
	res = _realloc(res, sizeof(char) * j, sizeof(char) * (j + 1));
	*(res + j) = '\0';
	if (can_free && str != NULL)
		free(str);
	return (res);
}

/**
 * dissolve_cmd_parts - Dissolves the parts of the command node
 * @node: The command node
 */
void dissolve_cmd_parts(cmd_t *node)
{
	int i;

	node->command = dissolve_tokens(node->command, TRUE);
	for (i = 0; i < node->args_count; i++)
	{
		*(node->args + i) = dissolve_tokens(*(node->args + i), TRUE);
	}
}
