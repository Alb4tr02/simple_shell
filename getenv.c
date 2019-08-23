#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "holberton.h"
#define MAX 1024
extern char **environ;
void getentorno(void)
{
	int i = 0, l = 0, fd = 0, m = 0, n = 0;
	ssize_t pos = 0;
	char buf[MAX];
	char *env = NULL;
	char *pathname = NULL;
	char *name = "/environ";
	pathname = getcwd(buf, MAX);
	for (; pathname[n]; n++)
		;
	for (; name[m]; m++)
		;
	for (m = 0; name[m]; m++, n++)
		pathname[n] = name[m];
	pathname[n] = 0;
	fd = open(pathname, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0777);
	while(environ[i])
	{
		for (l = 0; *(environ[i] + l); l++)
			;
		write(fd, environ[i], l + 1);
		i++;
	}
	close(fd);
	env = _getline(&pos, pathname);
	int ll = 0;
	for (; ll <= pos; ll++)
		if (env[ll] == 0)
			env[ll] = '\n';
	fd = open(pathname, O_WRONLY);
	write(fd, env, pos);
	close(fd);
	free(env);
}
