#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "main.h"

/**
 * new_cmd_node - Creates a new node
 *
 * Return: The pointer to the newly created noe
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
 * add_node_to_end - adds a node to the end of the list
 * @head: The pointer to the head of the list
 * @node: The node to add.
 */
void add_node_to_end(cmd_t **head, cmd_t **node)
{
	cmd_t *tail, *new_node;

	tail = head ? *head : NULL;
	while (tail != NULL && tail->next != NULL)
		tail = tail->next;
	new_node =  malloc(sizeof(cmd_t));
	if (new_node != NULL)
	{
		if (*node != NULL)
		{
			new_node->command = (*node)->command;
			new_node->args_count = (*node)->args_count;
			new_node->args  = (*node)->args;
			new_node->next_cond = (*node)->next_cond;
			free(*node);
			*node = NULL;
		}
		if (head == NULL)
			head = &new_node;
		else if (head != NULL && *head == NULL)
			*head = new_node;
		else if (tail != NULL)
			tail->next = new_node;
	}
}
