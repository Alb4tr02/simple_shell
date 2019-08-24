#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fcntl.h>
#include <unistd.h>

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
	char **argseach = NULL;
	int i = 0, j = 0, entero = 0, g, k;
	char *args[] = {"cd", "env", "history", "exit", "alias", NULL};
	char *filenames[] = {"h_cd.txt", "h_env.txt", "h_history.txt", "h_exit.txt", "h_alias.txt", NULL};
	char *buffer = NULL;
	char *buf = NULL;
	ssize_t a = 0;
	ssize_t *p = &a;

	argseach = h->args;
	buffer = malloc(1024);
	if (buffer == NULL)
		return (0);
	if(argseach[1][0] == 0)
	{
		printf ("escribe un segundo argumento por favor");
		return (0);
	}
	while (args[i] != NULL)
	{
		for (j = 0; args[i][j] != '\0'; j++)
		{
			if (argseach[1][j] - args[i][j] != 0)
			{
				entero = argseach[1][j] - args[i][j];
				break;
			}
		}
		if (entero == 0)
		{
			for (j = 0; filenames[i][j] != 0; j++)
				;
			getcwd(buffer, 1024);
			for (g = 0; buffer[g]; g++)
				;
			buffer[g] = '/';
			g++;
			for (k = 0; k < j; k++)
			{
				buffer[g] = filenames[i][k];
				g++;
			}
			buf = _getline(p, buffer);
			printf("%s\n", buf);
		}
		i++;
	}
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
	printf("función cd\n");
	return (0);
}
