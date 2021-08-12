#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "main.h"

cmd_t *new_cmd_node()
{
	cmd_t *node = NULL;

	node = malloc(sizeof(cmd_t));
	if (node != NULL)
	{
		node->command  = NULL;
		node->args_count = 0;
		node->args  = NULL;
		node->next_cond = SEP_OP;
		node->next = NULL;
	}
	return (node);
}

/**
 * free_list - Frees a cmd_t list
 * @head: The node at the beginning of the list
 */
void free_list(cmd_t *head)
{
	if (head)
	{
		if (head->next)
			free_list(head->next);
		if (head->command)
			free(head->command);
		if (head->args)
			free(head->args);
		if (head)
			free(head);
	}
}


/**
 * add_node_toend - adds a node to the end of the list
 * @head: head of the list
 * Return: void
 */

void add_node_toend(cmd_t **head)
{
	cmd_t *current = *head, *new = malloc(sizeof(cmd_t));

	if (new == NULL)
	{
		perror("memory allocation error on add_node_toend\n");
		return;
	}

	while (current)
	{
		if (current->next == NULL)
		{
			current->next = new;
			break;
		}
		current = current->next;
	}
	new->next = NULL;
}
