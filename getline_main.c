#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main (void)
{
	int status, j;
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
		//while (h != NULL)
		//{
		//	for (i = 0; **h->args != 0; i++)
		//	{
		//		printf("argumento : [%d]", **h->args);
		//		printf("\n");
		//		**h->args = **h->args;
		//	}
		//	h = h->next;
		//}
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
