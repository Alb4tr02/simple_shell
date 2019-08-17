#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main (void)
{
	int status;
	ssize_t i = 0;
	size_t a = 0;
	size_t *p = &a;
	char r = 'a';

	while (1)
	{
		status = 0;
		
		a = 0;
		char *buf = NULL;
		prompt();
		buf = _getline(p);
		//printf("%s", buf);
		command_t *h = _getargs(buf, p);
		if (!h)
			printf("no sirve esta mierda\n");
		char **pp = h->args;
		if (!pp)
			printf("no sirve esta mierda\n");
		if (fork() == 0)
		{
			status = execve(*pp, pp, NULL);
		}
		else
			wait(NULL);
		if (status == -1)
		{
			printf("Error.\n");
		}
		free(buf);
	}
	return (0);
}
