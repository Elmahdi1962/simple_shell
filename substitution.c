#include "main.h"

static char **expanded_aliases;
static int n;
static char *expansion;
static int exp_sz;

char is_valid_prev_char(char c)
{
	if (
		(c == ' ')
		|| (c == '\t')
		|| (c == ';')
		|| (c == '|')
		|| (c == '&')
		)
		return (TRUE);
	else
		return (FALSE);
}

token_t *process_alias_expansion(token_t **tokens)
{
	token_t *expanded_tokens = NULL;
	char prev_char = ' ';

	if (tokens == NULL)
		return (NULL);
	if (expansion != NULL)
	{
		free(expansion);
		expansion = NULL;
	}
	exp_sz = 0;
	if (expanded_aliases != NULL)
	{
		free_array(expanded_aliases, n);
		expanded_aliases = NULL;
	}
	n = 0;
	process_tokens(tokens, prev_char);
	expansion = _realloc(expansion, sizeof(char) * exp_sz, sizeof(char) * (exp_sz + 1));
	if (expansion != NULL)
	{
		*(expansion + exp_sz) = '\0';
		printf("Expansion: %s\n", expansion);
		expanded_tokens = tokenize_command_string(expansion);
		free(expansion);
		expansion = NULL;
	}
	free_token_t(*tokens);
	free_array(expanded_aliases, n);
	return (expanded_tokens);
}

void process_tokens(token_t **tokens, char prev_char)
{
	int i = 0;
	token_t *cur_token = NULL, *sub_tokens = NULL, *prev_token = NULL;
	char *alias_val = NULL;

	if (tokens == NULL)
		return;
	write(STDOUT_FILENO, "Processing alias\n", 17);
	cur_token = *tokens;
	while (cur_token != NULL)
	{
		if (
				((cur_token->type == TKN_WORD)	&& ((prev_token == NULL)
						|| (prev_token->type != TKN_WORD) || is_valid_prev_char(prev_char)))
				&& (str_in_arr(expanded_aliases, n, cur_token->value) == FALSE)
				&& (is_alias_name(cur_token->value) && is_alias(cur_token->value))
			)
		{
			alias_val = get_alias_value(cur_token->value);
			if ((alias_val != NULL) && (*alias_val != '\0'))
			{
				expanded_aliases = _realloc(expanded_aliases,
					sizeof(void *) * (n), sizeof(void *) * (n + 1));
				*(expanded_aliases + n) = str_copy(cur_token->value);
				n++;
				sub_tokens = tokenize_command_string(alias_val);
				write(STDOUT_FILENO, "alias_val: |", 12);
				write(STDOUT_FILENO, alias_val, str_len(alias_val));
				write(STDOUT_FILENO, "|\n", 2);
				/* *prev_char = *(alias_val + str_len(alias_val) - 1); */
				process_tokens(&sub_tokens, *(alias_val + str_len(alias_val) - 1));
				free_token_t(sub_tokens);
			}
		}
		else
		{
			expansion = _realloc(expansion, sizeof(char) * (exp_sz),
				sizeof(char) * (exp_sz + str_len(cur_token->value) + 1));
			if (expansion != NULL)
			{
				*(expansion + exp_sz) = ' ';
				exp_sz++;
				for (i = 0; i < str_len(cur_token->value); i++)
				{
					*(expansion + exp_sz) = *(cur_token->value + i);
					exp_sz++;
				}
			}
		}
		prev_token = cur_token;
		cur_token = cur_token->next;
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
