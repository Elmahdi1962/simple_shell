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

/**
 * str_cmp - Makes a comparison between two strings
 * @left: The string on the left side
 * @right: The string on the right side
 *
 * Return: -1 if the left is < than right, 1 if left is > right and othrwise 0
*/
int str_cmp(char *left, char *right)
{
	int i;

	if (left == NULL && right != NULL)
		return (-1);
	if (left != NULL && right == NULL)
		return (1);
	if (left == NULL && right == NULL)
	{
		return (0);
	}
	else
	{
		for (i = 0; *(left + i) != '\0' && *(right + i) != '\0'; i++)
		{
			if (*(left + i) == '\0' && *(right + i) != '\0')
				return (-1);
			if (*(left + i) != '\0' && *(right + i) == '\0')
				return (1);
			if (*(left + i) > *(right + i))
				return (1);
			if (*(left + i) < *(right + i))
				return (-1);
		}
		return (0);
	}
}

/**
 * str_copy - Makes a copy of a string
 * @str: The string to copy
 *
 * Return: The copied string, otherwise NULL
 */
char *str_copy(char *str)
{
	char *new_str;
	int i;
	int len = str_len(str);

	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str)
	{
		for (i = 0; i < len; i++)
			*(new_str + i) = *(str + i);
		*(new_str + i) = '\0';
	}
	return (new_str);
}


/**
 * str_cat - Concatenates two strings
 * @left: The left string
 * @right: The right string
 * @can_free: Specifies if the given strings can be freed
 *
 * Return: A pointer to the concatenated string
 */
char *str_cat(char *left, char *right, char can_free)
{
	int left_length = str_len(left);
	int right_length = str_len(right);
	int i;
	char *str;

	str = malloc(sizeof(char) * (left_length + right_length + 1));
	if (str)
	{
		for (i = 0; *(left + i) != '\0'; i++)
			*(str + i) = *(left + i);
		for (i = 0; *(right + i) != '\0'; i++)
			*(str + left_length + i) = *(right + i);
		*(str + left_length + i) = '\0';
	}
	if (can_free)
	{
		free(left);
		free(right);
	}
	return (str);
}

