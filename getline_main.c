#define MAX 1024
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
	int c1 = 0, c2 = 0;
	char *name = "/environ";
	char *pathname = NULL;
	char buffer[MAX];
	pathname = getcwd(buffer, MAX);
	for (; pathname[c1]; c1++)
		;
	for (; name[c2]; c2++, c1++)
		pathname[c1] = name[c2];
	pathname[c1] = 0;
	int pid = getpid();
	_getenv(pathname, pid);
	while (1)
	{
		status = 0;
		a = 0;
		char *buf = NULL;
		prompt();
		buf = _getline(p, NULL);
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
