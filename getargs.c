#include "holberton.h"
#include <stdio.h>

/**
 * istoken - verfy operators.
 * @c: character to verify
 * Return: 1 if there is coicidence or 0 if it is not
 */
int istoken(char c)
{
	int i = 0;
	char tokens[] = {'&', '|', '\0', '<', '>', -1};

	while (tokens[i++] != -1)
		if (tokens[i] == c)
			return (1);
	return (0);
}

/**
 * _getargs  - create a linked list that contains all arguments.
 * @buf: buffer with the string
 * @pos: pointer tu the actual buffer position
 * Return: a pointer to the linked list
 */
command_t *_getargs(char *buf, ssize_t *pos)
{
	ssize_t aux, aux2, p = 0;
	unsigned int size = 0, flag = 0;
	int sp, s, i, y, j;
	command_t *head, *args;

	head = NULL;
	while (p <= *pos)
	{
		aux = p;
		sp = 0;
		flag = 1;
		while (!istoken(buf[p]) && p <= *pos)
		{
			if (p == *pos && buf[p] != ' ')
				sp++;
			if (buf[p] == ' ')
			{
				if (flag)
					sp++;
				flag = 0;
			}
			else
				flag = 1;
			p++;
		}
		if (p != 0 && sp == 0)
			sp++;
		args = fill_nodes(buf, sp);
		add_node(&head, args);
	}

	return (head);
}

/**
* fill_nodes - create a linked list that contains all arguments.
* @buf: poiter to pointer to a space in memory
* @sp: size of args
* Return: a pointer to the linked list
*/
command_t *fill_nodes(char *buf, int *sp)
{
	char **args = NULL;
	int i, aux, aux2, s, y, j;

	*args = malloc(sizeof(char *) * (sp + 1));
	*(args + sp) = NULL;
	for (i = 0; sp > 0; sp--, i++)
	{
		aux2 = aux;
		for (s = 0; buf[aux] != ' ' && aux <= *pos; aux++, s++)
			;
		args[i] = malloc(sizeof(char) * (s + 1));
		if (!args[i])
		{
			for (y = 0; y < i; y++)
				free(args[y]);
			free(args);
			return (NULL);
		}
		for (j = 0; j < s; j++, aux2++)
			*(*(args + i) + j) = buf[aux2];
		*(*(args + i) + s) = 0;
		while (buf[aux] == ' ')
			aux++;
	}

	return (args)
}
