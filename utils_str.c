#include <stdlib.h>
#include "main.h"

/**
 * str_len - Computes the length of a string
 * @str: The source string
 *
 * Return: The length of the string.
 */
int str_len(char *str)
{
	int len = 0;

	while (str != NULL && *(str + len) != '\0')
		len++;
	return (len);
}

/**
 * mem_set - Fills a section of a string with a given character
 * \ (starts from position 0)
 * @str: The string containing the section to be filled
 * @n: The length of the section to fill
 * @c: The character to fill the section with
 */
void mem_set(char *str, int n, char c)
{
	int i;

	for (i = 0; str != NULL && i < n; i++)
		*(str + i) = c;
}

/**
 * trim_start - Makes a trimmed copy of a string
 * @str: The string whose beginning is to be trimmed
 * @c: The character to strip from the beginning of the string
 * @can_free: Specifies if the given string can be freed
 *
 * Return: The trimmed copy, otherwise NULL
 */
char *trim_start(char *str, char c, char can_free)
{
	int i, j, len;
	char *new_str;

	for (i = 0; *(str + i) != '\0' && *(str + i) == c; i++)
		;
	len = str_len(str) - i;
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str)
	{
		for (j = 0; *(str + i) != '\0'; i++)
		{
			*(new_str + j) = *(str + i);
			j++;
		}
		*(new_str + j) = '\0';
		if (can_free)
			free(str);
	}
	return (new_str);
}

/**
 * trim_end - Makes a trimmed copy of a string
 * @str: The string whose ending is to be trimmed
 * @c: The character to strip from the end of the string
 * @can_free: Specifies if the given string can be freed
 *
 * Return: The trimmed copy, otherwise NULL
 */
char *trim_end(char *str, char c, char can_free)
{
	char *new_str;
	int len = str_len(str);
	int i, j;

	for (i = len - 1; i >= 0 && *(str + i) == c; i--)
		;
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str)
	{
		for (j = 0; j <= i; j++)
			*(new_str + j) = *(str + j);
		*(new_str + j) = '\0';
		if (can_free)
			free(str);
	}
	return (new_str);
}

int str_cmp(char *left, char *right)
{
	int i;

	if (left == NULL && right != NULL)
		return (-1);
	if (left != NULL && right == NULL)
		return (1);
	if (left == NULL && right == NULL)
		return (0);
	if (left != NULL && right != NULL)
	{
		for (i = 0; *(left + i) != '\0' && *(right + i) != '\0'; i++)
		{
			if (*(left + i) == '\0' && *(right + i) != '\0')
				return (-1);
			if (*(left + i) != '\0' && *(right + i) == '\0')
				return (1);
			if (*(left + i) == '\0' && *(right + i) == '\0')
				return (0);
			if (*(left + i) > *(right + i))
				return (1);
			if (*(left + i) < *(right + i))
				return (0);
		}
	}
	return (-2);
}