#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
void prompt(void)
{
	int  y, r, p;
	p = r = y = 0;
	char *prompt = ">:v";
	char *yellow = "\033[1;33m";
	char *reset = "\033[0m";
	for (; reset[r]; r++)
		;
	for (; yellow[y]; y++)
		;
	for (; prompt[p]; p++)
		;
	write(1, yellow, y);
	write(1, prompt, p);
	write(1, reset, r);
}
int main (void)
{
	int status;
	ssize_t i = 0;
	size_t a = 0;
	size_t *p = &a;
	char *buf = NULL;
	char r = 'a';
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
	prompt();
	if (status == -1)
	{
		printf("Error.\n");
	}
	free(buf);
	return (0);
}
