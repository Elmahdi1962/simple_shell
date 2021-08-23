#include "main.h"

/**
 * tokenize_command_string - Converts a line of text into a list of tokens
 * @str: The line of text
 *
 * Return: The list of tokens
 */
token_t *tokenize_command_string(char *str)
{
	int i = 0, len = 0;
	char error = FALSE;
	token_t *tokens = NULL;

	while (((str != NULL) && (*(str + i) != '\0')) &&
		((*(str + i) != '#') && (error == FALSE)))
	{
		if (*(str + i) == '#')
		{
			skip_comment(str, i, &len);
		}
		else if ((*(str + i) == '|') || (*(str + i) == '&'))
		{
			add_token_to_end(&tokens,
				create_token(read_operator(str, i, &len, &error), TKN_OP));
		}
		else if (*(str + i) == ';')
		{
			add_token_to_end(&tokens,
				create_token(str_copy(";"), TKN_SEP_OP)), len = 1;
		}
		else if (is_whitespace(*(str + i)))
		{
			len = 1;
		}
		else
		{
			add_token_to_end(&tokens,
				create_token(read_word(str, i, &len), TKN_WORD));
		}
		i += len;
	}
	if (error)
	{
		free_token_t(&tokens);
		return (NULL);
	}
	return (tokens);
}

/**
 * skip_comment - Skips a line of text containing a comments
 * @str: The source text
 * @o: The offset in the source text
 * @len_out: A pointer to the length of the positions to be skipped
 */
void skip_comment(char *str, int o, int *len_out)
{
	int i = 0;

	if ((str != NULL) && (*(str + o) == '#'))
	{
		while (*(str + o + i) != '\0')
			i++;
		if (len_out != NULL)
			*len_out = i + 1;
	}
}

/**
 * read_operator - Reads an operator from a given text
 * @str: The source text
 * @o: The offset in the source text
 * @len_out: A pointer to the length of the positions to be skipped
 * @error: A pointer to the error flag
 *
 * Return: The operator that was read, otherwise NULL
 */
char *read_operator(char *str, int o, int *len_out, char *error)
{
	int i = 0, j;
	char buf[3] = {0}, *op, *buf0, *buf1;

	if ((*(str + 0 + o) == '|') && (*(str + 1 + o) == '|'))
	{
		buf[0] = '|';
		buf[1] = '|';
		i = 2;
	}
	else if ((*(str + 0 + o) == '&') && (*(str + 1 + o) == '&'))
	{
		buf[0] = '&';
		buf[1] = '&';
		i = 2;
	}
	else
	{
		buf0 = *((char **)get_shell_prop(EXEC_NAME_ID));
		buf1 = long_to_str(get_line_num());

		write(STDERR_FILENO, buf0, str_len(buf0));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, buf1, str_len(buf1));
		write(STDERR_FILENO, ": Syntax error: \"", 17);
		write(STDERR_FILENO, (str + 1 + o), 1);
		write(STDERR_FILENO, "\" unexpected\n", 13);
		*error = TRUE;
		*len_out = 1;
		return (NULL);
	}
	op = malloc(sizeof(char) * (i + 1));
	if (op != NULL)
	{
		for (j = 0; j < i; j++)
			op[j] = buf[j];
		op[j] = '\0';
	}
	if (len_out != NULL)
		*len_out = i;
	return (op);
}

/**
 * read_word - Reads an operator from a given text
 * @str: The source text
 * @o: The offset in the source text
 * @len_out: A pointer to the length of the positions to be skipped
 *
 * Return: The word that was read, otherwise NULL
 */
char *read_word(char *str, int o, int *len_out)
{
	int i = 0, k, quote_o = 0;
	char quote = '\0', *word;

	while (*(str + i + o) != '\0')
	{
		if (is_quote(*(str + i + o)))
		{
			if (quote == FALSE)
				quote = *(str + i + o), quote_o = TRUE;
			else if ((*(str + i + o) == quote))
				quote = '\0', quote_o = FALSE;
		}
		else if (quote_o == FALSE)
		{
			if ((*(str + i + o) == '&') || (*(str + i + o) == '|')
				|| (*(str + i + o) == ';') || is_whitespace(*(str + i + o)))
				break;
		}
		i++;
	}
	word = malloc(sizeof(char) * (i + 1));
	if (word != NULL)
	{
		for (k = 0; k < i; k++)
			*(word + k) = *(str + k + o);
		*(word + k) = '\0';
	}
	if (len_out != NULL)
		*len_out = i;
	return (word);
}
