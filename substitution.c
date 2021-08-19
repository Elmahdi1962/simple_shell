#include "main.h"

/* static char *previous_aliases; */

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
