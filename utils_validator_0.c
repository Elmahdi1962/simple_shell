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
 * is_variable_expandible - Checks if the next character after the variable
 * insertion character ($) in the string can be expanded
 * @str: The source string
 * @pos: The current position in the string
 * @quote: The active quote character in the string
 * @quote_o: The status of the quote character in the string
 *
 * Return: TRUE if the variable can be expanded, otherwise FALSE
 */
char is_variable_expandible(char *str, int pos, char quote, char quote_o)
{
	char extra_expansion_chars[] = "$?-*!";
	char next_char;
	int i;

	if (str == NULL)
		return (FALSE);
	if ((*(str + pos + 1) != '\0')
		&& (((quote == '"') && (quote_o == TRUE)) || (quote_o == FALSE)))
	{
		next_char = *(str + pos + 1);
		for (i = 0; extra_expansion_chars[i] != '\0'; i++)
		{
			if (next_char == extra_expansion_chars[i])
				return (TRUE);
		}
		if (is_digit(next_char)
			|| is_letter(next_char))
			return (TRUE);
	}
	return (FALSE);
}
