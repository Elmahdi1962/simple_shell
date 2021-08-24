#include "main.h"

/**
 * _realloc - Reallocates a memory block
 * @ptr: The pointer to the previous memory block
 * @old_size: The size of the old memory block
 * @new_size: The size of the new memory block
 *
 * Return: The pointer to the new memory block otherwise NULL
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;
	unsigned int min_size = old_size < new_size ? old_size : new_size;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (ptr != NULL)
	{
		if (new_size == 0)
		{
			free(ptr);
			return (NULL);
		}
		new_ptr = malloc(new_size);
		if (new_ptr != NULL)
		{
			for (i = 0; i < min_size; i++)
				*((char *)new_ptr + i) = *((char *)ptr + i);
			free(ptr);
			return (new_ptr);
		}
		free(ptr);
		return (NULL);
	}
	else
	{
		new_ptr = malloc(new_size);
		return (new_ptr);
	}
}

/**
 * free_array - Frees a 2d array
 * @arr: The pointer to the array to free
 * @length: The length of the given array
 */
void free_array(char **arr, int length)
{
	int i;

	if (arr != NULL)
	{
		for (i = 0; (i < length) && (arr[i] != NULL); i++)
		{
			if (arr[i] != NULL)
			{
				free(arr[i]);
				arr[i] = NULL;
			}
		}
		if (arr != NULL)
			free(arr);
		arr = NULL;
	}
}
