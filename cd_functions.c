#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#define MAX 500

char *clpath(char *path)
{
	int j = 0, i = 0;
	char *cpypath = NULL;
	char *filter = NULL;
	char *aux = NULL;
	for (; path[j]; j++)
		;
	filter = filtro1(path);
	cpypath = filtro2(filter);
	aux = filtro1(cpypath);
	free(cpypath);
	cpypath = aux;
	for (i = 0; cpypath[i]; i++)
	{
		if (aredots(cpypath, i, j))
		{
			aux = filtro2(cpypath);
			free(cpypath);
			cpypath = aux;
			i = 0;
			continue;
		}
	}
	free(filter);
	return (cpypath);
}
int absolutepath(char *path)
{
	DIR *dir = NULL;
	char *pwd = NULL;
	char *cpypath = NULL;
	char *root = "/";
	int flag = 1;
	pwd = _getenvvar("PWD");
	cpypath = clpath(path);
	if (cpypath[0] == '/' && cpypath[1] == '.' && cpypath[2] == '.'
	    && cpypath[3] == 0)
	{
		free(cpypath);
		cpypath = root;
		flag = 0;
	}
	dir = opendir(cpypath);
	if (dir)
	{
		closedir(dir);
		chdir(cpypath);
		_setenv("PWD", cpypath);
		_setenv("OLDPWD", pwd);
		free(pwd);
		if (flag)
			free(cpypath);
		return (0);
	}
	else
	{
		free(pwd);
		if (flag)
			free(cpypath);
		return (-1);
	}
	return (0);
}
int _cd(command_t *h)
{
	char **args = NULL;
	char *path = NULL;
	char *home = NULL;

	args = h->args;
	path = args[1];
	if (path == NULL || path[0] == '~')
	{
		home = _getenvvar("HOME");
		absolutepath(home);
		free(home);
	}
	else if (path[0] == '-' && path[1] == 0)
		chtopreviousdir();
	else if (path[0] == '.' && path[1] == '.' && path[2] == 0)
		darthVader();
	else if (path[0] == '.' && path[1] == 0)
		lukeSkywalker();
	else
		absolutepath(path);
	/*else
	  relativepath(path);*/
	return (0);
}
