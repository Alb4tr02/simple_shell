#define MAX 1024
#include "holberton.h"

/**
 * _getargs - function that gets the arguments.
 * @pos: pointer to the actual buffer position.
 * Return: pointer to the buffer that stores the line.
 */
char **_getargs(char *buf)
{
	args *head = NULL;
	int len;
	char *arg;

	len = 0;
	while (*buf != '\0')
	{

		for (i = 0; buf[len] != ' '; len++)
		{
			i++;
			arg[i] = buf[len];
		}
		add_node(&head, *arg);
	}
	return (&head);

}
