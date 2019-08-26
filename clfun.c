#include "holberton.h"
#include <stdio.h>
#define MAX 500
int look(char *fun)
{
	int pos = 0, flag = 0, i = 0;
	char *current = NULL;
	char *built[] =  {"history", "exit", "env", "help", "cd", NULL};
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
char *currentpath(void)
{
	int g = 0;
	char *py =_calloc(MAX, MAX);
	getcwd(py, MAX);
	for (; py[g]; g++)
		;
	py[g] = '/';
	g++;
	py[g] = 0;
	return (py);
}
char **getdir(void)
{
	int sp = 0, i = 0, l = 0, aux = 0, j = 0, flag = 1;
	int p = 0;
	char *path;
	char *var = "PATH";
	char **dir = NULL;
	path = _getenvvar(var);
	if (!path || path[0] == 0)
		return (NULL);
	for (; path[i]; i++)
		if (path[i] == ':')
			sp++;
	if (path[0] != 0)
		sp++;
	if (sp == 0)
		return (dir);
	dir = _calloc((sp + 1), sizeof(void *));
	dir[sp] = NULL;
	for (i = 0; i < sp; i++)
	{
		if (path[0] == ':' && flag)
		{
			dir[0] = currentpath();
			i++, j++;
			flag = 0;
		}
		aux = j;
		for (l = 0 ; j < 1024 && path[j] && path[j] != ':'; j++, l++)
		        ;
		if (l == 0)
		{
			dir[i] = currentpath();
			j++;
			continue;
		}
		j++;
		dir[i] = _calloc(sizeof(char), (l + 2));
		for (p = 0; path[aux] && aux < 1024 && path[aux] != ':'; aux++, p++)
			*(dir[i] + p) = path[aux];
		*(dir[i] + p) = '/';
		p++;
		*(dir[i] + p) = 0;
		aux++;
		j = aux;
	}
	free(path);
	return (dir);
}
void freedir(char **dir, char *arg)
{
	int l = 0;

	if (arg)
		free(arg);
	for (l = 0; dir[l]; l++)
		free(dir[l]);
	free(dir[l]);
	free(dir);
}
int  clfun(char **arg)
{
	char *com = NULL;
	char **dir = NULL;
	char *crtdir = NULL;
	char *aux = NULL;
	unsigned int i = 0, l = 0, la = 0;
	int res, fd  = 0;
	int found = 1;
	res = look(*arg);
	if (res == BUILT)
		return (BUILT);
	com = *arg;
	if (*(*(arg + 0) + 0) == '/')
		return (EXT);
	dir = getdir();
	if (dir == NULL)
	{
		return (res);
	}
	for (; com[la]; la++)
		;
	la++;
	while (dir[i])
	{
		crtdir = dir[i];
		for (l = 0; crtdir[l]; l++)
			;
		aux = _calloc(sizeof(char), (la + l + 1));
		for (l = 0; crtdir[l]; l++)
			aux[l] = crtdir[l];
		for (la = 0; com[la]; la++, l++)
			aux[l] = com[la];
		aux[l] = 0;
		fd = open(aux, O_RDONLY);
		if (fd != -1)
		{
			freedir(dir, *arg);
			*arg = aux;
			found = 0;
			close(fd);
			break;
		}
		i++;
		free(aux);
	}
	if (found)
	{
		freedir(dir, NULL);
		res = -1;
	}
	return (res);
}
