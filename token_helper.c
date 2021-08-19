#include "main.h"

/**
 * add_token_to_end - Adds a token to the end of a list
 * @head: The head of the list of tokens
 * @tkn: The token to add
 */
void add_token_to_end(token_t **head, token_t *tkn)
{
	token_t *tail = NULL;

	if (head != NULL)
	{
		tail = *head;
		while ((tail != NULL) && (tail->next != NULL))
			tail = tail->next;
		if (tail == NULL)
			*head = tkn;
		else
			tail->next = tkn;
	}
	else
	{
		head = &tkn;
	}
}

/**
 * create_tokenn - Creates a new token
 * @value: The value of the token
 * @type: The type of the token
 *
 * Return: a pointer to the newly created token
 */
token_t *create_token(char *value, char type)
{
	token_t *tkn = NULL;

	tkn = malloc(sizeof(token_t));
	if (tkn != NULL)
	{
		tkn->value = value;
		tkn->type = type;
		tkn->next = NULL;
	}
	return (tkn);
}

/**
 * free_token_t - Frees a token_t list
 * @head: The node at the beginning of the list
 */
void free_token_t(token_t *head)
{
	if (head != NULL)
	{
		if (head->next != NULL)
			free_token_t(head->next);
		if (head->value != NULL)
			free(head->value);
		if (head != NULL)
			free(head);
	}
}

token_t *get_token_at_index(int idx, token_t **head)
{
	int i = 0;
	token_t *cur = NULL;

	if (head != NULL)
	{
		cur = *head;
		while (cur != NULL)
		{
			if (i == idx)
				return (cur);
			cur = cur->next;
			i++;
		}
	}
	return (NULL);
}
