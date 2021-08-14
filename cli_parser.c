#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

cmd_t *parse_cmd_line(char *line)
{
	int i = 0, j, c;
	cmd_t *head = NULL, *node = NULL;
	char prev_token = TKN_BEG, *word, *error = NULL;

	if (line != NULL && *line != '\0')
	{
		for (i = 0; *(line + i) != '#' && *(line + i) != '\0' && error == NULL;)
		{
			if (is_whitespace(*(line + i)) && prev_token != TKN_BEG)
			{
				prev_token = TKN_SPACE, j = 0, i++;
			}
			else if (is_operator(*(line + i)))
			{
				read_operator(line, &i, prev_token, &node, &head, &error);
				prev_token = TKN_OP;
			}
			else
			{
				j = prev_token != TKN_WORD ? i : j;
				word = read_word(line, &i);
				if (word != NULL)
				{
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
				prev_token = TKN_WORD;
			}
		}
		if (node != NULL)
			add_node_to_end(&head, &node);
	}
	return (head);
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
		&& ((str_cmp(";", op_s) == 0)
		|| (str_cmp("||", op_s) == 0)
		|| (str_cmp("&&", op_s) == 0)))
	{
		if (node != NULL && *node != NULL)
			(*node)->next_cond = ((*op_s == '|') ? OR_OP
													: ((*op_s == '&') ? AND_OP : SEP_OP));
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

char *read_word(char *line, int *pos)
{
	int i = *pos, j = *pos, k = 0, quote_d = 0, len;
	char quote = 0, *word;

	while (*(line + i) != '\0')
	{
		if (is_quote(*(line + i)))
		{
			if (quote == 0)
			{
				quote = *(line + i);
				quote_d = 1;
			}
			else if ((*(line + i) == quote))
			{
				quote = 0;
				quote_d = 0;
			}
		}
		else if (quote_d == 0)
		{
			if (is_operator(*(line + i)) || (is_whitespace(*(line + i))) || (*(line + i) == '#'))
			{
				break;
			}
		}
		i++, len++;
	}

	word = malloc(sizeof(char) * (len + 1));
	if (word != NULL)
	{
		for (k = 0; k < len; k++)
		{
			*(word + k) = *(line + j);
			j++;
		}
		*(word + k) = '\0';
	}
	*pos = i;
	return (word);
}

/**
	 * token_types:
	 * 0 -> Beginning
	 * 1 -> word
	 * 2 -> space
	 * 3 -> operator
	 */

cmd_t *parse_cmd_line_1(char *line)
{
	int i, j, k, c = 0, quote_d = 0;
	cmd_t *head = NULL, *node = NULL;
	char prev_token = TKN_BEG, *word = NULL;

	if (line != NULL && *line != '\0')
	{
		for (i = 0; *(line + i) != '#' && *(line + i) != '\0'; i++)
		{
			if (is_whitespace(*(line + i)) && quote_d == 0)
			{
				prev_token = 2, j = 0;
			}
			else if ((*(line + i) == '|') || ((*(line + i) == '&')) || (*(line + i) == ';'))
			{
				if ((*(line + i + 1) != '\0') && (prev_token == TKN_WORD || prev_token == TKN_SPACE) && ((*(line + i) == ';') || ((*(line + i + 1) == '|') || ((*(line + i + 1) == '&')))))
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
					perror("Syntax error\n");
				}
			}
			else if (*(line + i) == '#')
			{
				break;
			}
			else
			{
				j = prev_token != TKN_WORD ? i : j;
				if (is_whitespace(*(line + i + 1)) || is_operator(*(line + i + 1)) || ((*(line + i + 1) == '\0')))
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
				prev_token = TKN_WORD;
			}
		}
		if (node != NULL)
			add_node_to_end(&head, &node);
	}
	return (head);
}
