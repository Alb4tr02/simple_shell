#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int _history(command_t *h, command_t *copy)
{
	(void)h;
	freecommand(copy);
	return (0);
}

/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int _env(command_t *h, command_t *copy)
{
	(void)h;
	freecommand(copy);
	return (0);
}

/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int _help(command_t *h, command_t *copy)
{
	(void)h;
	freecommand(copy);
	return (0);
}

/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int _cd(command_t *h, command_t *copy)
{
	(void)h;
	freecommand(copy);
	return (0);
}
