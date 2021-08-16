#include "main.h"

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
	char *str = NULL;

	str = malloc(sizeof(char) * (left_length + right_length + 1));
	if (str != NULL)
	{
		for (i = 0; left != NULL && *(left + i) != '\0'; i++)
			*(str + i) = *(left + i);
		for (i = 0; right != NULL && *(right + i) != '\0'; i++)
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

/**
 * copy_range - Copies a range of chracters from a to b inclusive
 * @str: The string to copy from
 * @s: The start index
 * @b: The end index
 *
 * Return: A newly created string, otherwise NULL
 */
char *copy_range(char *str, int a, int b)
{
	int len = str_len(str), i;
	int start = MIN(a, b);
	int end = MAX(a, b);

	res = malloc(sizeof(char) * (end - start + 2));
	if (start < len && end <= len)
	{
		for (i = 0; i < (end - start + 1); i++)
			*(res + i) = *(str + start + i);
		*(res + i) = '\0';
	}
	return (res);
}

/**
 * str_split - Splits a string into smaller strings at a given character
 * @str: The string to split
 * @c: The character at which to perform the split
 * @len: The pointer which would contain the number of smaller strings
 * @can_free: Specifies if the string can be freed
 *
 * Return: A pointer to the first string in the array of strings
*/
char **str_split(char *str, char c, int *len, char can_free)
{
	int i, j = 0, n = 0;
	char **strs = NULL;

	if (str == NULL)
	{
		perror("str is null\n");
		return (NULL);
	}
	if (str != NULL)
	{
		for (i = 0; *(str + i) != '\0'; i++)
		{
			if (*(str + i) == c)
			{
				strs = _realloc(strs, sizeof(void *) * n, sizeof(void *) * (n + 1));
				*(strs + n) = copy_range(str, j, i - 1);
				j = i + 1;
				n++;
			}
		}
		if (*(str + i - 1) != c)
		{
			strs = _realloc(strs, sizeof(void *) * n, sizeof(void *) * (n + 1));
			*(strs + n) = copy_range(str, j, i);
			n++;
		}
	}
	if (len != NULL)
		*len = n;
	if (can_free && str != NULL)
		free(str);
	return (strs);
}
