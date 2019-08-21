#include "holberton.h"
#include <stdio.h>
#define MAX 1024
int look(char *fun)
{
	int pos = 0, flag = 0, i = 0;
	char *current;
	char *built[] =  {"history", "exit", "env", "help", NULL};
	while (built[i])
	{
		current = built[i];
		for (pos = 0; current[pos] && fun[pos]; pos++)
		{
			if (current[pos] == fun[pos])
			{
				if (current[pos + 1] == 0 && fun[pos +1] == 0)
					return (BUILT);
			}
			else
				break;
		}
		i++;
	}
	return ((flag == 0) ? EXT: BUILT);
}
char **getdir(void)
{
	int sp = 0, i = 0, l = 0, aux = 0, j = 0;
	int p = 0;
	char path[MAX];
	char *var = "PATH";
	char **dir = NULL;
	getvar(var, path);
	for (; path[i]; i++)
		if (path[i] == ':')
			sp++;
	if (path[0] != 0)
		sp++;
	if (sp == 0)
		return (dir);
	dir = malloc(sizeof(void *) * (sp + 1));
	dir[sp] = NULL;
	for (i = 0; i < sp; i++)
	{
		aux = j;
		for (l = 0 ; path[j] != ':'; j++, l++)
			;
		j++;
		dir[i] = malloc(l + 1);
		for (p = 0; path[aux] != ':'; aux++, p++)
			*(dir[i] + p) = path[aux];
		*(dir[i] + p) = '/';
		p++;
		*(dir[i] + p) = 0;
	}
	return (dir);
}
int  clfun(char **arg)
{
	char *com = NULL;
	char **dir = NULL;
	char *crtdir = NULL;
	char *aux = NULL;
	unsigned int i = 0, l = 0, la = 0;
	int res, fd  = 0;
	int found = 0;
	com = *arg;
	dir = getdir();
	if (*(*(arg + 0) + 0) == '/')
		return (EXT);
	res = look(*arg);
	for (; com[la]; la++)
		;
	la++;
	while (dir[i])
	{
		crtdir = dir[i];
		for (l = 0; crtdir[l]; l++)
			;
		aux = malloc(la + l);
		for (l = 0; crtdir[l]; l++)
			aux[l] = crtdir[l];
		for (la = 0; com[la]; la++, l++)
			aux[l] = com[la];
		aux[l] = 0;
		fd = open(aux, O_RDONLY);
		if (fd != -1)
		{
			free(*arg);
			*arg = aux;
			for (l = 0; dir[l]; l++)
				free(dir[l]);
			free(dir[l]);
			free(dir);
			found = 0;
			close(fd);
			break;
		}
		i++;
	}
	if (found)
		res = -1;
	return (res);
}
