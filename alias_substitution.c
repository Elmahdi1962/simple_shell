#include "main.h"

/* The array of names of aliases that have been expanded */
static char **expanded_aliases;
/* The length of the array of alias names */
static int n;
/* The expansion been created by the alias subsitution */
static char *expansion;
/* The length of the expansion being created by the alias substitution */
static int exp_sz;

/**
 * is_valid_prev_char - Checks if the given character is a valid character \
 * for the likely subsitution of a subsequent word that is an alias name
 * @c: The character to check
 *
 * Return: TRUE or FALSE
 */
char is_valid_prev_char(char c)
{
	if ((c == ' ')
			|| (c == '\t')
			|| (c == ';')
			|| (c == '|')
			|| (c == '&')
		)
	{
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}
}

/**
 * process_alias_expansion - Prosesses a list of tokens by subsituting aliases
 * @tokens: The tokens to be processed
 *
 * Return: The newly created tokens
 */
token_t *process_alias_expansion(token_t **tokens)
{
	token_t *expanded_tokens = NULL;

	if ((tokens == NULL) || (*tokens == NULL))
		return (NULL);
	process_tokens(tokens);
	expansion = _realloc(expansion, sizeof(char) * exp_sz,
		sizeof(char) * (exp_sz + 1));
	if (expansion != NULL)
	{
		*(expansion + exp_sz) = '\0';
		expanded_tokens = tokenize_command_string(expansion);
		free(expansion);
		expansion = NULL;
		exp_sz = 0;
	}
	free_token_t(tokens);

	free_array(expanded_aliases, n);
	expanded_aliases = NULL;
	n = 0;
	return (expanded_tokens);
}

/**
 * process_tokens - Processes a list of tokens by substituting \
 * aliases with their values
 * @tokens: The list of tokens
 * @prev_char
 */
void process_tokens(token_t **tokens)
{
	int i = 0;
	token_t *cur_token = NULL, *sub_tokens = NULL, *prev_token = NULL;
	char *alias_val = NULL, prev_char = 0;

	if ((tokens == NULL) || (*tokens == NULL))
		return;
	cur_token = *tokens;
	while (cur_token != NULL)
	{
		if (((cur_token->type == TKN_WORD)	&& ((prev_token == NULL)
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
				*(expanded_aliases + n) = str_copy(cur_token->value), n++;
				sub_tokens = tokenize_command_string(alias_val);
				prev_char = *(alias_val + str_len(alias_val) - 1);
				process_tokens(&sub_tokens);
				free_token_t(&sub_tokens);
			}
		}
		else
		{
			expansion = _realloc(expansion, sizeof(char) * (exp_sz),
				sizeof(char) * (exp_sz + str_len(cur_token->value) + 1));
			if (expansion != NULL)
			{
				*(expansion + exp_sz) = ' ', exp_sz++;
				for (i = 0; i < str_len(cur_token->value); i++, exp_sz++)
					*(expansion + exp_sz) = *(cur_token->value + i);
			}
		}
		prev_token = cur_token, cur_token = cur_token->next;
	}
}
