#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * funexc - call execvp or buitin functions.
 *
 * Return: no return
 */
void funexc(command_t *h)
{
	command_t *copy = NULL;

	while(h)
	{
		copy = h;
		if (h->id == 0)
			_extern(h);
		else
			_built(h);
		h = h->next;
		freecommand(copy);
	}
}

/**
 * funexc - call execvp or buitin functions.
 *
 * Return: no return
 */
void _extern(command_t *h)
{

	int status = 0, pid = 0;

	if (!h->args)
		printf("no sirve esta mierda\n");
	pid = fork();
	if (pid == 0)
	{
		status = execve(*h->args, h->args, NULL);
		if (status == -1)
			salir(h);
	}
	else
		wait(NULL);
}


/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
void _built(command_t *h)
{
	int j = 0, entero = 0, i = 0;
	char **argseach = NULL;
	builtin commandsbuilt[] =  {{"history", _history}, {"exit", salir}, {"env", _env},{"help", _help}, {"cd", _cd}, {NULL}};

	entero = 0;
	i = 0;
	argseach = h->args;

	while (commandsbuilt[i].built != NULL)
	{
		entero = 0;
		for (j = 0; argseach[0][j] != '\0'; j++)
		{
			if (argseach[0][j] - commandsbuilt[i].built[j] != 0)
			{
				entero = argseach[0][j] - commandsbuilt[i].built[j];
				break;
			}

		}
		if (entero == 0)
			commandsbuilt[i].f(h);

		i++;
	}
	if (entero == 0 && argseach[0][j] != '\0')
		entero = argseach[0][j] - commandsbuilt[i].built[j];
}

/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int salir(command_t *h)
{
	command_t *cpy = NULL;
	while (h)
	{
		cpy = h->next;
		freecommand(h);
		h = cpy;
	}
	exit (0);
}
