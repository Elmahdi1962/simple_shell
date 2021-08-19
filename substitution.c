#include "main.h"

/* static char *previous_aliases; */

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

char is_valid_prev_char(char c)
{
	if (is_whitespace(c)
		|| (c == ';')
		|| (c == '|')
		|| (c == '&')
		)
		return (TRUE);
	else
		return (FALSE);
}

char str_in_list(char **arr, int n, char *str)
{
	int i;

	for (i = 0; (arr != NULL) && (i < n); i++)
	{
		if (str_eql(*(arr + i), str))
			return (TRUE);
	}
	return (FALSE);
}

void process_alias_expansion(token_t **tokens, char **expansions, int *n, char prev_char)
{
	token_t *cur_token = NULL, *sub_tokens = NULL, *prev_token = NULL;
	char *alias_val = NULL;

	return;
	if (tokens != NULL)
	{
		write(STDOUT_FILENO, "Processing alias\n", 17);
		cur_token = *tokens;

		while (cur_token != NULL)
		{
			if (
				((cur_token->type = TKN_WORD) && is_valid_prev_char(prev_char))
				&& (str_in_list(expansions, *n, cur_token->value) == FALSE)
				&& (is_alias_name(cur_token->value) && is_alias(cur_token->value))
				)
			{
				alias_val = get_alias_value(cur_token->value);
				if ((alias_val != NULL))
				{
					sub_tokens = tokenize_command_string(alias_val);
					write(STDOUT_FILENO, "alias_val: ", 11);
					write(STDOUT_FILENO, alias_val, str_len(alias_val));
					write(STDOUT_FILENO, "\n", 1);
				}

				expansions = _realloc(expansions,
					sizeof(void *) * (*n), sizeof(void *) * (*n + 1));
				*(expansions + *n) = str_copy(cur_token->value);
				(*n)++;
				process_alias_expansion(&sub_tokens, expansions, n, *(alias_val + str_len(alias_val) - 1));
				/* insert sub tokens */
				get_token_tail(&sub_tokens)->next = cur_token->next;
				if (prev_token != NULL)
					prev_token->next = sub_tokens;
				else
					cur_token = sub_tokens;
			}
			prev_token = cur_token;
			cur_token = cur_token->next;
		}
	}
}

token_t *get_token_tail(token_t **head)
{
	token_t *tail = NULL;

	if (head != NULL)
	{
		tail = *head;
		while ((tail != NULL) && (tail->next != NULL))
			tail = tail->next;
	}
	return (tail);
}
