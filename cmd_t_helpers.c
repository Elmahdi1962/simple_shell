#include "main.h"

/**
 * new_cmd_node - Creates a new node
 *
 * Return: The pointer to the newly created node
 */
cmd_t *new_cmd_node()
{
	cmd_t *node = NULL;

	node = malloc(sizeof(cmd_t));
	if (node != NULL)
	{
		node->command  = NULL;
		node->args_count = 0;
		node->args  = NULL;
		node->next_cond = OP_NONE;
		node->next = NULL;
	}
	return (node);
}

/**
 * free_cmd_t - Frees a cmd_t list
 * @head: The node at the beginning of the list
 */
void free_cmd_t(cmd_t **head)
{
	if (head != NULL)
	{
		if (*head != NULL)
		{
			if ((*head)->next != NULL)
				free_cmd_t(&((*head)->next));
			if ((*head)->command != NULL)
				free((*head)->command);
			(*head)->command = NULL;
			if ((*head)->args != NULL)
				free_array((*head)->args, (*head)->args_count);
			free(*head);
		}
		*head = NULL;
	}
}

/**
 * add_node_to_end - adds a node to the end of the list
 * @head: The pointer to the head of the list
 * @node: The node to add.
 */
void add_node_to_end(cmd_t **head, cmd_t **node)
{
	cmd_t *tail = NULL;

	tail = head != NULL ? *head : NULL;
	while (tail != NULL && tail->next != NULL)
		tail = tail->next;
	if (node != NULL)
	{
		if (head == NULL)
			head = node;
		else if ((head != NULL) && (*head == NULL))
			*head = *node;
		else if (tail != NULL)
			tail->next = *node;
	}
}

/**
 * get_cmd_t_tail - Gets the tail of a cmd_t list
 * @head: The head of the cmd_t list
 *
 * Return: The tail, otherwise NULL
 */
cmd_t *get_cmd_t_tail(cmd_t *head)
{
	cmd_t *tail = head;

	while ((tail != NULL) && (tail->next != NULL))
		tail = tail->next;
	return (tail);
}
