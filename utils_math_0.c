#include "main.h"

/**
 * str_to_int - Converts a string to an int
 * @num: The string to convert
 *
 * Return: The converted number
 */
int str_to_int(char *num)
{
	int i = 1, len, exp = 1;
	int res = 0;

	len = str_len(num);
	for (i = len - 1; i >= 0; i--)
	{
		if (*(num + i) == '-')
			res *= -1;
		else if (is_digit(*(num + i)))
		{
			res += (*(num + i) - '0') * exp;
			exp *= 10;
		}
	}
	return (res);
}

