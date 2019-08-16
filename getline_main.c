#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main (void)
{
<<<<<<< HEAD
	ssize_t a = 0;
	ssize_t *p = &a;
	char go[] = "tony";
	char *buf = go;
	char **args;

	buf = _getline(p);
	args = getargs(buf);
	printf("%s", buf);
	printf("%s", args);
=======
	int status;
	ssize_t i = 0;
	size_t a = 0;
	size_t *p = &a;
	char *buf = NULL;
	char r = 'a';
	char *prompt = "ko:)";
	//printf("%s", prompt);
	write(1, prompt, 4);
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
	printf("(*< --o--o");
	if (status == -1)
	{
		printf("Error.\n");
	}
>>>>>>> b195efcdec08fdcad857354d3d4ae42d1c3b2ec2
	free(buf);
	return (0);
}
