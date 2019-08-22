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
	command_t *copy = h;

	while(h)
	{

		if (h->id == 0)
			_extern(h);
		else
			_built(h, copy);
		h = h->next;
	}
}

/**
 * funexc - call execvp or buitin functions.
 *
 * Return: no return
 */
void _extern(command_t *h)
{

	command_t *cpy;
	int status;

	cpy = h;
	if (!h->args)
		printf("no sirve esta mierda\n");
	if (fork() == 0)
	{
		status = execve(*h->args, h->args, NULL);
	}
	else
		wait(NULL);
	if (status == -1)
	{
		printf("Error.\n");
	}
	h = h->next;
	freecommand(cpy);
}


/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
void _built(command_t *h, command_t *copy)
{
	int j, entero, i;
	char **argseach;
	builtin commandsbuilt[] =  {{"history", _history}, {"exit", salir}, {"env", _env},{"help", _help}, {"cd", _cd}, {NULL}};

	entero = 0;
	i = 0;
	while (h)
	{
		argseach = h->args;

		while (commandsbuilt[i].built != NULL)
		{
			for (j = 0; argseach[0][j] != '\0'; j++)
			{
				if (argseach[0][j] - commandsbuilt[i].built[j] != 0)
				{
					entero = argseach[0][j] - commandsbuilt[i].built[j];
					break;
				}

			}
			if (entero == 0)
				commandsbuilt[i].f(h, copy);

			i++;
		}
		h = h->next;
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
int salir(command_t *h, command_t *copy)
{
	(void)h;
	freecommand(copy);
	return (0);


}
