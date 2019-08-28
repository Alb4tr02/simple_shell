#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * imprimir_error - print error when command not found.
 * @h: node tha has the builtin command
 *
 * Return: no return
 */
void imprimir_error(command_t *h)
{
	int l1 = 0;
	char *sp = ": ";
	char *n = NULL;
	char *cont = NULL;
	char *com = NULL;
	char *msg = ": not found";
	char sl = '\n';
	int a = 2;

	com = h->args[0];
	cont = print_number(h->cont);
	n = h->name;
	l1 = _strlen(n);
	write(1, n, l1);
	write(1, sp, 2);
	l1 = _strlen(cont);
	write(1, cont, l1);
	write(1, sp, 2);
	l1 = _strlen(com);
	write(1, com, l1);
	l1 = _strlen(msg);
	write(1, msg, l1);
	write(1, &sl, 1);
	free(cont);
	setstatus(&a);
}
/**
 * funexc - call execvp or buitin functions.
 * @h: pointer to the head of the linked list
 *
 * Return: no return
 */
void funexc(command_t *h)
{
	command_t *copy = NULL;
	static int cont;

	cont++;
	while (h)
	{
		h->cont = cont;
		copy = h;
		if (h->id == -1)
			imprimir_error(h);
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
	int ex = 0;
	int f = 2;
	char **env = _setenv(NULL, NULL);

	if (!h->args)
		printf("no sirve esta mierda\n");
	pid = fork();
	if (pid == 0)
	{
		status = execve(*h->args, h->args, env);
		if (status == -1)
		{
			setstatus(&f);
			salir(h);
		}
		else
			setstatus(&ex);
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
	alias *al = NULL, *ali = NULL;
	int i = 0, res = 0;
	char *buffer = NULL;

	/*if (h->args[1] != NULL)
	{
		res = _atoi(h->args[1]);
		res = (res < 0) ? res * -1 : res;
		}*/
	buffer = getpath();
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
	free(buffer);
	exit(res % 255);
}
