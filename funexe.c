#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * funexc - call execvp or buitin functions.
 * @h: pointer to the head of the linked list
 *
 * Return: no return
 */
void funexc(command_t *h)
{
	command_t *copy = NULL;

	while (h)
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
 * _extern - call execvp or buitin functions.
 * @h: pointer to the head of the linked list
 *
 * Return: no return
 */
void _extern(command_t *h)
{

	int status = 0, pid = 0;
	char **env = _setenv(NULL, NULL);

	if (!h->args)
		printf("no sirve esta mierda\n");
	pid = fork();
	if (pid == 0)
	{
		status = execve(*h->args, h->args, env);
		if (status == -1)
			salir(h);
	}
	else
		wait(NULL);
}


/**
* _built - call different builtins.
* @h: node tha has the builtin command
*
* Return: no return
*/
void _built(command_t *h)
{
	int j = 0, entero = 0, i = 0;
	char **argseach = NULL;
	builtin commandsbuilt[] =  {{"history", _history}, {"exit", salir},
				    {"env", _env}, {"help", _help},
				    {"cd", _cd}, {"setenv", _setenviron},
				    {"unsetenv", _unsetenv}, {"alias", _alias},
				    {NULL}};

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
* salir - exit from the function.
* @h: copy of head of linked list
*
* Return: no return
*/
int salir(command_t *h)
{
	command_t *cpy = NULL;
	char **env = NULL;
	alias *al = NULL;
	alias *ali = NULL;
	int i = 0;

	while (h)
	{
		cpy = h->next;
		freecommand(h);
		h = cpy;
	}
	env = _setenv(NULL, NULL);
	for (; env[i]; i++)
		free(env[i]);
	free(env[i]);
	free(env);
	al = setalias(NULL);
	ali = al;
	while (al)
	{
		free(al->name);
		free(al->value);
		ali = al->next;
		free(al);
		al = ali;
	}
	exit (0);
}
