#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main (void)
{
	int status;
	ssize_t a = 0;
	ssize_t *p = &a;
	char *buf = NULL;
	command_t *h;

	while (1)
	{
		status = 0;
		a = 0;
		prompt();
		buf = _getline(p);
		h = _getargs(buf, p);
		if (!h)
			printf("no sirve esta mierda\n");
		while (h != NULL)
		{
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
		}
			free(buf);
	}
	return (0);
}
