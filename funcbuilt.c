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
	env = _setenv("PATH", NULL);
	while (env[i])
	{
		for(l = 0; env[i][l]; l++)
			;
		write(STDIN_FILENO, env[i], l);
		write(STDIN_FILENO, &sl, 1);
		i++;
	}
	return (0);
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
	int pos = 0, l = 0, i = 0;
	char **env = NULL;
	char *pwd = NULL;
	char *newpwd = NULL;
	env = _setenv("PATH", NULL);
	pos = buscar(env, "PWD");
	pwd = env[pos];
	for (; pwd[l]; l++)
		if (pwd[l] == '/')
			i = l;
	newpwd = _calloc(i + 2, sizeof(char));
	for (l = 0; pwd[l] && l <= i; l++)
		newpwd[l] = pwd[l];
	return (newpwd);
}
int chtopreviousdir(void)
{
	char *oldpwd = NULL;
	char *pwd = NULL;
	DIR *dir = NULL;
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
		free(pwd);
		free(oldpwd);
		return (0);
	}
	return (-1);
}
int _cd(command_t *h)
{
	char **args = NULL;
	char *path = NULL;
	args = h->args;
	path = args[1];
	if (path[0] == '-' && path[1] == 0)
		chtopreviousdir();
	/*else if (path[0] == '.' && path[1] == '.' && path[2] == 0)
		darthVader();
	else if (path[0] == '.' && path[1] == 0)
		lukeSkywalker();
	else if (path[0] == '/')
		absolutepath(path);
	else
	relativepath(path);*/
	return (0);
}
