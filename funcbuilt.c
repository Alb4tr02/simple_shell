#include "holberton.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#define MAX 500

/**
* _history - show history of commands.
* @h: node tha has the builtin command

* Return: no return
*/
int _history(command_t *h)
{
	(void)h;
	printf("función history\n");
	return (0);
}

/**
* _env - show all environment variables.
* @h: node tha has the builtin command
*
* Return: no return
*/
int _env(command_t *h)
{
	char **env = NULL, **args = NULL;
	int i = 0, l = 0;
	char sl = '\n';

	(void)h;
	args = h->args;
	if (args[1] != NULL)
	{
		search_file_env(h);
		return (0);
	}
	env = _setenv(NULL, NULL);
	while (env[i])
	{
		for (l = 0; env[i][l]; l++)
			;
		write(1, env[i], l);
		write(1, &sl, 1);
		i++;
	}
	return (0);
}

/**
 * _setenviron - set environ.
 * @h: node tha has the builtin command
 *
 * Return: o if succes or -1
 */
int _setenviron(command_t *h)
{
	char **args = NULL;
	char *err = "ERROR\n";
	int i = 0, er = 2;
	args = h->args;
	for (; args[i]; i++)
		;
	if (i != 3)
	{
		write(STDERR_FILENO, err, _strlen(err));
		setstatus(&er);
		return (-1);
	}
	_setenv(args[1], args[2]);
	return (0);
}

/**
 * _unsetenv - unset variable.
 * @h: node tha has the builtin command
 *
 * Return: no return
 */
int _unsetenv(command_t *h)
{
	char **args = NULL;
	char *var = NULL;
	char *err = "Error\n";
	int i = 0;
	args = h->args;
	for (; args[i]; i++)
		;
	if (i != 2)
	{
		write(1, err, _strlen(err));
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
		write(1, err, _strlen(err));
		return (-1);
	}
	return (-1);
}
/**
* getpath - get current path
*
* Return: no return
*/

char *getpath(void)
{

	static int flag = 0;
	static char *path;

	if (!flag)
	{
		path = _calloc(500,1);
		if (path == NULL)
			return (0);
		path = getcwd(path, 500);
		flag = 1;
	}
	return (path);
}

/**
 * _help - show help document of some functions.
 * @h: node tha has the builtin command
 *
 * Return: no return
 */
int _help(command_t *h)
{
	char **argseach = NULL;
	int i = 0, j = 0, entero = 0, g, k, longbuf = 0, l;
	char *args[] = {"cd", "env", "history", "exit", "alias", "help", "setenv",
			"unsetenv", NULL};
	char *filenames[] = {"h_cd.txt", "h_env.txt", "h_history.txt",
			     "h_exit.txt", "h_alias.txt", "h_help.txt",
			     "h_setenv.txt", "h_unsetenv.txt", NULL};
	char *buf = NULL;
	ssize_t a = 0;
	ssize_t *p = &a;
	char *pathandfile = NULL, *buffer = NULL, *filejusthelp = "justhelp.txt";

	argseach = h->args;
	pathandfile = _calloc(500, 1);
	buffer = getpath();
	for (l = 0; buffer[l]; l++)
		pathandfile[l] = buffer[l];
	if (argseach[1] == NULL)
	{
       		pathandfile[l] = '/';
		l++;
		for (k = 0; k < 12; k++, l++)
			pathandfile[l] = filejusthelp[k];
		buf = _getline(p, pathandfile);
		longbuf = _strlen(buf);
		write(1, buf, longbuf);
		free(pathandfile);
		free(buf);
		return (0);
	}
	if (argseach[1][0] == 0)
		return (0);
	while (args[i] != NULL)
	{
		entero = 0;
		for (j = 0; args[i][j] != '\0'; j++)
		{
			if (argseach[1][j] - args[i][j] != 0)
			{
				entero = argseach[1][j] - args[i][j];
				break;
			}
		}
		if (entero == 0)
		{
			for (j = 0; filenames[i][j] != 0; j++)
				;
			for (g = 0; buffer[g]; g++)
				;
			pathandfile[g] = '/';
			g++;
			for (k = 0; k < j; k++, g++)
				pathandfile[g] = filenames[i][k];
			buf = _getline(p, pathandfile);
			longbuf = _strlen(buf);
			write(1, buf, longbuf);
			free(pathandfile);
			free(buf);
		}
		i++;
	}
	return (0);
}


/**
* getvaderdir - get variable directory.
*
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
	if (newpwd[0] == 0)
		newpwd[0] = '/';
	return (newpwd);
}

/**
* chtopreviousdir - give previous directory.
*
* Return: no return
*/
int chtopreviousdir(void)
{
	char *oldpwd = NULL;
	char *pwd = NULL;
	char *home = NULL;
	int l = 0;
	char *err = "Error\n";
	char sl = '\n';

	oldpwd = _getenvvar("OLDPWD");
	pwd = _getenvvar("PWD");
	if (!oldpwd)
	{
		home = _getenvvar("HOME");
		absolutepath(home);
		free(home);
		free(pwd);
		return (-1);
	}
	else
	{
		if (chdir(oldpwd) == -1)
		{
			write(1, err, _strlen(err));
			return (-1);
		}
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

/**
* darthCader - change directory father.
*
* Return: return 0
*/
int darthVader()
{
	char *newpwd = NULL;
	char *pwd = NULL;
	char *err = "./hsh: cd: ";
	char *err2 = ": No such file or directory\n";
	pwd = _getenvvar("PWD");
	newpwd = getvaderdir();
	if (chdir(newpwd) == -1)
	{
		write(STDERR_FILENO, err, _strlen(err));
		write(STDERR_FILENO, newpwd, _strlen(newpwd));
		write(STDERR_FILENO, err2, _strlen(err2));
		free(pwd);
		free(newpwd);
		return(-1);
	}
	_setenv("PWD", newpwd);
	_setenv("OLDPWD", pwd);
	free(pwd);
	free(newpwd);
	return (0);
}

/**
 * lukeskywalker - return 0.
 *
 * Return: no return
 */
int lukeSkywalker(void)
{
	return (0);
}

/**
 * aerodots - filter (.. /).
 * @path: pointer to path
 * @pos: position in buffer to verify if it is . . and /
 * @size: size of buffer
 * Return: 0 or 1
 */
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

/**
 * nexdir - give next dire after .. /.
 * @filter: pointer to buffer
 * @i: position before directory
 * Return: position of the next dir or -1
 */
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

/**
 * filtro1 - delete extra /.
 * @path: pointer to path
 *
 * Return: no return
 */
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

/**
 * filtro2 - if we have two points after directory .
 * @filter: pointer to the buffer
 *
 * Return: pointer to the copy path
 */
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
