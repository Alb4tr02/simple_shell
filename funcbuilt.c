#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 500
extern char **environ;
/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int _history(command_t *h)
{
	(void)h;
	printf("función history\n");
	return (0);
}

/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int _env(command_t *h)
{
	(void)h;
	printf("función env\n");
	return (0);
}

/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int _help(command_t *h)
{
	(void)h;
	printf("función help\n");
	return (0);
}

/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int _cd(command_t *h)
{
	(void)h;
/*	char **args = NULL;
	char *path = NULL;
	char *home = NULL;
	char *pwd = NULL;
	char *oldpwd = NULL;
	args = h->args;
	path = args[1];
	if (!path)
	{
		home = _calloc(MAX, MAX);
		getvar("HOME", home);
		setvar()*/
	printf("función cd\n");
	return (0);
}
