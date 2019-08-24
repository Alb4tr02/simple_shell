#define MAX 1024
#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
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
	free(args[i]);
	free(args);
	free(h);
}
int main (void)
{
	ssize_t a = 0;
	ssize_t *p = &a;
	char *buf = NULL;
	command_t *h = NULL;
	while (1)
	{
		a = 0;
		signal(SIGINT, handle_signal);
		prompt();
		buf = _getline(p, NULL);
		if (buf[0] == '\n')
		{
			free (buf);
			continue;
		}
		h = _getargs(buf, p);
		free(buf);
		if (!h)
			return (0);
		funexc(h);
	}
	return (0);
}
