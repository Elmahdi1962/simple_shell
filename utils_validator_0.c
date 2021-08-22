#include "main.h"

/**
 * is_digit - Checks if the given character is a digit character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_digit(char c)
{
	return (c >= '0' && c <= '9' ? TRUE : FALSE);
}

/**
 * is_whitespace - Checks if the given character is a whitespace character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_whitespace(char c)
{
	int i;
	char set[] = {' ', '\t', '\r', '\n'};

	for (i = 0; i < 4; i++)
		if (c == set[i])
			return (TRUE);
	return (FALSE);
}

/**
 * is_letter - Checks if the given character is a letter
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_letter(char c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? TRUE : FALSE);
}

/**
 * is_quote - Checks if the given character is a quote character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_quote(char c)
{
	return ((c == '\'' || c == '"') ? TRUE : FALSE);
}

/**
 * is_variable_expandible - Checks if a variable in the string can be expanded
 * @str: The source string
 * @pos: The current position in the string
 * @quote: The active quote character in the string
 * @quote_o: The status of the quote character in the string
 *
 * Return: TRUE if the variable can be expanded, otherwise FALSE
 */
char is_variable_expandible(char *str, int pos, char quote, char quote_o)
{
	if (str == NULL)
		return (FALSE);
	if (((quote == '"') && (quote_o == TRUE)) || (quote_o == FALSE))
	{
		if ((*(str + pos + 1) == '$')
			|| (*(str + pos + 1) == '?')
			|| (*(str + pos + 1) == '_')
			|| is_letter(*(str + pos + 1)))
			return (TRUE);
	}
	return (FALSE);
}
