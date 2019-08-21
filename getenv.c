#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "holberton.h"
#define MAX 1024
void getentorno(void)
{
	extern char *environ[];
	int i = 0, l = 0, fd = 0, m = 0, n = 0;
	char buf[MAX];
	char *pathname = NULL;
	char *name = "/environ";
	pathname = getcwd(buf, MAX);
	for (; pathname[n]; n++)
		;
	for (; name[m]; m++)
		;
	for (m = 0; name[m]; m++, n++)
		pathname[n] = name[m];
	pathname[m] = 0;
	printf("%s\n", pathname);
	fd = open(pathname, O_WRONLY | O_APPEND);
	while(environ[i])
	{
		for (l = 0; *(environ[i] + l); l++)
			;
		write(fd, environ[i], l + 1);

	}
	char end[] = {-1};
	write(fd, end, 1);
	close(fd);
	return;
/*
		ssize_t ht = 0;
	ssize_t *hht = &ht;
	int i = 0, jk = 0, fd = 0;
	int cpyid;
	int  pos = 0, total = 0;
	char buf[MAX];
	int ps = 0;
	char *path = "/proc/";
	char *pn;
	char *env;
	char *en = "/environ";
	for (; path[ps]; ps++)
		;
	cpyid = pid;
	for (i = 0; pid; pid = pid / 10, i++)
		;
	char *num = malloc(i + 1);
	pid = cpyid;
	sprintf(num, "%d", pid);
	pn = malloc(ps + i + 10);
	for (ps = 0; path[ps]; ps++)
		pn[ps] = path[ps];
	for (i = 0; num[i]; i++, ps++)
		pn[ps] = num[i];
	for (jk = 0; en[jk]; jk++, ps++)
		pn[ps] = en[jk];
	pn[ps] = 0;
	total = _readandcpy(pn, pathname, buf);
	free(pn);
	env = _getline(hht, pathname);
	int ll = 0;
	for (; ll <= *hht; ll++)
		if (env[ll] == 0)
			env[ll] = '\n';
	fd = open(pathname, O_WRONLY);
	write(fd, env, *hht);
	close(fd);
	return (0);
*/
}
