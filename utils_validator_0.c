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
	return ((c == ' ' || c == '\t' || c == '\r') ? TRUE : FALSE);
}

/**
 * is_operator - Checks if the given character is an operator character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_operator(char c)
{
	return ((c == ';' || c == '|' || c == '&') ? TRUE : FALSE);
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
