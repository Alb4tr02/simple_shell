#define MAX 1024
#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * freecommand - free linked list.
 * @h: head node of the linked list.
 *
 * Return: pointer to the new adress of data.
 */
void freecommand(command_t *h)
{
	int i = 0;
	char **args = NULL;

	args = h->args;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(h->name);
	free(args[i]);
	free(args);
	free(h);
}

/**
* main - void.
*
* Return: o if success.
*/
int main(int argc, char **argv)
{
	ssize_t a = 0;
	ssize_t *p = &a;
	command_t *h = NULL;
	size_t cnt = 0;
	char c, sl = '\n';
	char *buf = NULL;
	int flag = 1, flag1 = 1;

	getpath();
	if (argc > 1)
	{
		buf = _getline(&a, argv[1]);
		flag1 = 0;
		goto getarg;
	}
	while (flag1)
	{
inicio:
		a = 0;
		signal(SIGINT, handle_signal);
		prompt();
		cnt = 0;
		sl = '\n';
		buf = _calloc(4096 * 2, 1);
		flag = 1;
		while(read(STDIN_FILENO, &c, 1) == 1)
		{
			if (c == 4 && cnt == 0)
				break;
			if (c == '\n' && cnt == 0)
			{
				free(buf);
				goto inicio;
			}
			if(c == '\n' && cnt != 0)
			{
				buf[cnt] = 0;
				flag = 0;
				break;
			}

			buf[cnt++] = c;
			a++;
		}
		a++;
		if(cnt == 0 && buf[0] == 0)
		{
			write(STDIN_FILENO, &sl, 1);
			free(buf);
			salir(NULL);
		}
		if (flag)
			write(STDIN_FILENO, &sl, 1);
		if (buf[0] == '\n')
		{
			free (buf);
			continue;
		}

getarg:
		buffer_filter(&buf, p);
		h = _getargs(buf, p, argv[0]);
		free(buf);
		if (!h)
			return (0);
		funexc(h);
	}
	return (0);
}
