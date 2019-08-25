#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#define MAX 500
extern char **environ;
/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int _history(command_t *h)
{
	(void)h;
	printf("función history\n");
	return (0);
}

/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int _env(command_t *h)
{
	(void)h;
	char **env = NULL;
	int i = 0, l = 0;
	char sl = '\n';
	env = _setenv(NULL, NULL);
	while (env[i])
	{
		for(l = 0; env[i][l]; l++)
			;
		write(1, env[i], l);
		write(1, &sl, 1);
		i++;
	}
	return (0);
}
int _setenviron(command_t *h)
{
	char **args = NULL;
	int i = 0;
	args = h->args;
	for (; args[i]; i++)
		;
	if (i != 3)
	{
		printf("Error\n");
		return (-1);
	}
	_setenv(args[1], args[2]);
	return (0);
}
int _unsetenv(command_t *h)
{
	char **args = NULL;
	char *var = NULL;
	int i = 0;
	args = h->args;
	for (; args[i]; i++)
		;
	if (i != 2)
	{
		printf("Error\n");
		return (-1);
	}
	var = _getenvvar(args[1]);
	if (var)
	{
		_setenv(args[1], NULL);
		free(var);
		return (0);
	}
	else
	{
		printf("Error\n");
		return (-1);
	}
	return (-1);
}
/**
* funexc - call execvp or buitin functions.
* @h: node tha has the builtin command
* @copy: copy of head of linked list
* Return: no return
*/
int _help(command_t *h)
{
	(void)h;
	printf("función help\n");
	return (0);
}

/**
 * funexc - call execvp or buitin functions.
 * @h: node tha has the builtin command
 * @copy: copy of head of linked list
 * Return: no return
 */
char  *getvaderdir(void)
{
	int l = 0, i = 0;
	char *pwd = NULL;
	char *newpwd = NULL;
	pwd = _getenvvar("PWD");
	for (; pwd[l]; l++)
		if (pwd[l] == '/')
			i = l;
	newpwd = _calloc(i + 2, sizeof(char));
	for (l = 0; pwd[l] && l < i; l++)
		newpwd[l] = pwd[l];
	free(pwd);
	return (newpwd);
}
int chtopreviousdir(void)
{
	char *oldpwd = NULL;
	char *pwd = NULL;
	DIR *dir = NULL;
	int l = 0;
	char sl = '\n';
	oldpwd = _getenvvar("OLDPWD");
	pwd = _getenvvar("PWD");
	if (!oldpwd)
	{
		printf("OLDPWD not set error");
		free(pwd);
		return (-1);
	}
	else
	{
		dir = opendir(oldpwd);
		if (dir == NULL)
		{
			printf("ERROR\n");
			return (-1);
		}
		closedir(dir);
		chdir(oldpwd);
		_setenv("OLDPWD", pwd);
		for(; oldpwd[l]; l++)
			;
		write(1, oldpwd, l);
		write(1, &sl, 1);
		free(pwd);
		free(oldpwd);
		return (0);
	}
	return (-1);
}
int darthVader()
{
	char *newpwd = NULL;
	char *pwd = NULL;
	DIR *dir = NULL;
	pwd = _getenvvar("PWD");
	newpwd = getvaderdir();
	dir = opendir(newpwd);
	if (dir == NULL)
	{
		printf("Error :'v \n");
		free(pwd);
		free(newpwd);
		return(-1);
	}
	closedir(dir);
	chdir(newpwd);
	_setenv("PWD", newpwd);
	_setenv("OLDPWD", pwd);
	free(pwd);
	free(newpwd);
	return (0);
}
int lukeSkywalker(void)
{
	return (0);
}
int aredots(char *path, int pos, int size)
{
	if (path[pos] && path[pos + 1] && path[pos + 2])
	{
		if (path[pos] == '/' && path[pos + 1] == '.'
		    && path[pos + 2] == '.')
		{
			if ((pos + 3) <= size)
			{
				if ((path[pos + 3]) == 0 ||
				    (path[pos + 3]) == '/')
					return (1);
			}
		}
	}
	return (0);
}
int nextdir(char *filter, int i)
{
	if (!filter[i])
		return (-1);
	i++;
	for (; filter[i]; i++)
		if (filter[i] == '/')
			return(i);
	return (-1);
}
char *filtro1(char *path)
{
	char *filter = NULL;
	int j = 0, seek = 0, i = 0;
	for (; path[j]; j++)
		;
	filter = _calloc(j + 1, sizeof(char));
	for (; path[i]; i++)
	{
		if (path[i] == '/')
		{
			if (path[i + 1] == 0)
				break;
			if ((i + 1 <= j) && path[i + 1] == '/')
				continue;
			filter[seek] = path[i];
			seek++;
		}
		else
		{
			filter[seek] = path[i];
			seek++;
		}
	}
	return (filter);
}
char *filtro2(char *filter)
{
	char *cpypath = NULL;
	int j = 0, pos = 0, i = 0, cnt = 0;
	for (; filter[j]; j++)
		;
	cpypath = _calloc(j + 1, sizeof(char));

	for (i = 0; i <= j && filter[i]; i++)
	{
		if (i == 0 && aredots(filter, i, j))
		{
			i += 2;
			continue;
		}
		pos = nextdir(filter, i);
		if (pos == -1)
		{
			for (; filter[i]; i++, cnt++)
				cpypath[cnt] = filter[i];
			break;
		}
		if (aredots(filter, pos, j))
		{
			i = pos + 2;
			continue;
		}
		for (; i <= pos && filter[i]; i++, cnt++)
			cpypath[cnt] = filter[i];
		i--;
	}
	return (cpypath);
}
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
		printf("Error\n");
		return (-1);
	}
	//printf("ruta: %s\n", cp ypath);
	return (0);
}
int _cd(command_t *h)
{
	char **args = NULL;
	char *path = NULL;
	char *home = NULL;

	args = h->args;
	path = args[1];
	if (path == NULL)
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
