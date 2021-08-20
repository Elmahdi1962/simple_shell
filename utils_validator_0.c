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
 * is_tilde_expansion_char - Checks if the given character is a \
 * tilde expansion character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_tilde_expansion_char(char c)
{
	if ((c == '/')
		|| (c == '\0')
		|| (c == ':')
		|| (c == '-')
		|| (c == '+')
		)
		return (TRUE);
	else
		return (FALSE);
}
