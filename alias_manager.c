#include "main.h"

/* The array of aliases in this shell program */
static alias_t **Alias_List;
/* The number of aliases in this shell program */
static int Alias_Count;

/**
 * manage_aliases - Performs some management operations \
 * on the aliases
 * @op: The operation to perform
 */
void manage_aliases(char op)
{
	int i;

	if (op == MO_INIT)
	{
		Alias_Count = 0;
		Alias_List = NULL;
	}
	else if (op == MO_FREE)
	{
		if (Alias_List != NULL)
		{
			for (i = 0; i < Alias_Count; i++)
			{
				if (*(Alias_List + i) != NULL)
				{
					if ((*(Alias_List + i))->name != NULL)
						free((*(Alias_List + i))->name);
					if ((*(Alias_List + i))->value != NULL)
						free((*(Alias_List + i))->value);
					free(*(Alias_List + i));
				}
			}
			if (Alias_List != NULL)
				free(Alias_List);
		}
	}
}

/**
 * add_alias - Adds an alias to the list of aliases \
 * or replaces the value if it exists
 * @name: The name of the alias
 * @value: The value of the alias
 */
void add_alias(char *name, char *value)
{
	int i;

	if (is_alias(name))
	{
		for (i = 0; i < Alias_Count; i++)
		{
			if (str_eql(name, (*(Alias_List + i))->name))
			{
				if ((*(Alias_List + i))->value != NULL)
					free((*(Alias_List + i))->value);
				(*(Alias_List + i))->value = value;
			}
		}
	}
	else
	{
		Alias_List = _realloc(Alias_List, sizeof(alias_t) * Alias_Count,
			sizeof(alias_t) * (Alias_Count + 1));
		*(Alias_List + Alias_Count) = malloc(sizeof(alias_t));
		if (*(Alias_List + Alias_Count) != NULL)
		{
			(*(Alias_List + Alias_Count))->name = name;
			(*(Alias_List + Alias_Count))->value = value;
		}
		Alias_Count++;
	}
}

/**
 * get_alias_value - Retrieves the value of an alias
 * @str: The name of the alias to retrieve
 *
 * Return: The value of the alias, otherwise NULL
 */
char *get_alias_value(char *str)
{
	int i;

	if (Alias_List == NULL)
		return (NULL);
	for (i = 0; i < Alias_Count; i++)
	{
		if (str_eql(str, (*(Alias_List + i))->name))
			return ((*(Alias_List + i))->value);
	}
	return (NULL);
}

/**
 * get_aliases - Retrieves the aliases available and stores the \
 * length in the given parameter
 * @len: The pointer that contains the number of aliases available
 *
 * Return: The list of aliases
 */
alias_t **get_aliases(int *len)
{
	*len = Alias_Count;
	return (Alias_List);
}
