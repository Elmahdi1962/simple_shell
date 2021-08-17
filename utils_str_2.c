#include "main.h"

/**
 * str_replace - Replaces a string with a given string in another string
 * @str: The source string
 * @sub_str: The string to look for in the source string
 * @rep_str: The string to use as a replacement
 * @can_free: Specifies whether the given strings can be freed
 *
 * Return: The string containing the replaced values, otherwise, NULL
*/
char *str_replace(char *str, char *sub_str, char *rep_str, char can_free)
{
	char *res = str != NULL ? str_copy(str) : NULL, *tmp;
	int rep_len = str_len(rep_str);
	int sub_len = str_len(sub_str);
	int res_len = str_len(str);
	int i = 0, j = 0, a, b, c;

	if (res != NULL && sub_str != NULL && rep_str != NULL)
	{
		while (res != NULL && *(res + i) != '\0')
		{
			if (*(res + i) == *sub_str)
			{
				for (j = 0; (*(sub_str + j) != '\0') && (*(res + i) != '\0'); j++, i++)
				{
					if (*(sub_str + j) != *(res + i))
						break;
				}
				i -= j;
				if (j == sub_len)
				{
					/* make replacement */
					res_len = res_len + (rep_len == sub_len ? 0 :  rep_len - sub_len);
					tmp = malloc(sizeof(char) * (res_len + 1));
					if (tmp != NULL)
					{
						for (a = 0, b = 0, c = 0; a < res_len; a++)
						{
							c =  (a == i) ? i + sub_len : c;
							if (a >= i && a < (i + rep_len))
							{
								*(tmp + a) = *(rep_str + b);
								b++;
							}
							else
							{
								*(tmp + a) = *(res + c);
								c++;
							}
						}
						*(tmp + a) = '\0';
					}
					free(res);
					res = tmp;
					i += (rep_len == sub_len ? rep_len :  rep_len - sub_len);
				}
			}
			i++;
		}
	}
	if (can_free)
	{
		free(str);
		free(sub_str);
		free(rep_str);
	}
	return (res);
}

/**
 * long_to_str - Converts a long to its string representation
 * @num: The long integer
 *
 * Return: The string representation of the long integer
 */
char *long_to_str(long num)
{
	char *str;
	long rem = num;
	char sign = rem < 0 ? -1 : 1;
	char size = 20, j;

	str = malloc(sizeof(char) * (size + 1));
	if (str)
	{
		*(str + size) = '\0';
		mem_set(str, size, '0');
		j = size - 1;
		if (rem == 0)
			*(str + j) = '0';

		while ((sign == -1 && rem < 0) || (sign == 1 && rem > 0))
		{
			*(str + j) = (rem % 10) * sign + '0';
			rem /= 10;
			j--;
		}
		if (sign < 0)
			*(str + j) = '-';
		str = trim_start(str, '0', TRUE);
		str = num == 0 ? str_cat("0", "", FALSE) : str;
	}
	return (str);
}

/**
 * rep_range - Replaces a range of characters in a string
 * @str: The source string
 * @val: The value to use as a replacement
 * @a: The starting index
 * @b: The ending index
 *
 * Return: The replaced string, otherwise NULL
 */
char *rep_range(char *str, char *val, int a, int b)
{
	int len = str_len(str), in_len = str_len(val), i = 0, j = 0, k = 0;
	int start = MIN(a, b), end = MAX(a, b), size;
	char *res = NULL;
	int out_len = end - start + 1;

	size = len + (in_len == out_len ? 0 :  in_len - out_len);
	res = malloc(sizeof(char) * (size + 1));
	if (res != NULL)
	{
		for (i = 0; i < size; )
		{
			if (i == start)
			{
				for (j = 0; j < in_len; j++)
				{
					*(res + i) = *(val + j);
					i++;
				}
				k = start + out_len;
			}
			else
			{
				*(res + i) = *(str + k);
				k++;
				i++;
			}
		}
		*(res + i) = '\0';
	}
	return (res);
}
