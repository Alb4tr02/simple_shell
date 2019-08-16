#include "holberton.h"
/**
 * add_node - adds a new node at the beginning of a list_t list.
 * @head: the list of elements
 * @args: string to be stored
 * Return: direction of the new node
 */
command_t *add_node(command_t **head, char **args)
{
	int flag = 1;
	command_t *p = *head;
	command_t *new = malloc(sizeof(command_t));

	do {
		if (!p || !(p->next))
		{
			if (!new)
				return (NULL);
			new->args = args;
			new->next = NULL;
			if (!p)
			{
				*head = new;
				return (new);
			}
			p->next = new;
			flag = 0;
		}
		else
			p = p->next;
	} while (flag);
	return (new);
}
