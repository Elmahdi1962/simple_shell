#include <stdlib.h>
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
