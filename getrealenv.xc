#include <stdio.h>
#include "holberton.h"
extern char **environ;
char **getrealenv(void)
{
	static int flag = 1;
	static char **cpyenv;
	int i = 0, l = 0, j =0;
	if (flag)
	{
		while (environ[i])
			i++;
		cpyenv = _calloc((i + 1),  sizeof(char *));
		cpyenv[i] = NULL;
		for (j = 0; j < i; j++)
		{
			l = 0;
			while (environ[j][l])
				l++;
			cpyenv[j] = _calloc(l + 1, sizeof(char));
			for (l = 0; environ[j][l]; l++)
				cpyenv[j][l] = environ[j][l];
			cpyenv[j][l] = 0;
		}
		flag = 0;
	}
	return (cpyenv);
}
int buscar(char **environ, char *varname)
{
	int i = 0, j = 0, flag = 1, aux = 0;
	while (environ[i])
	{
		if (varname[0] == environ[i][0] )
		{
			flag = 1, j = 0;
			for (; varname[j]; j++)
				if (varname[j] != environ[i][j])
					flag = 0;
			if (flag && environ[i][j] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

char **_setenv(char *varname, char *valor)
{
	static char **env = NULL;
	static int flag = 1;
	if (flag)
	{
		env = getrealenv();
		flag = 0;
	}
	int pos = 0, l1 = 0, l2 = 0;
	char *newvar = NULL;
	if (valor)
	{
		while (varname[l1])
			l1++;
		while (valor[l2])
			l2++;
		newvar = _calloc(l1 + l2 + 2, sizeof(char));
		for (l1 = 0; varname[l1]; l1++)
			newvar[l1] = varname[l1];
		newvar[l1] = '=';
		l1++;
		for (l2 = 0; valor[l2]; l2++, l1++)
			newvar[l1] = valor[l2];
		newvar[l1] = 0;
		pos = buscar(env, varname);
		free(env[pos]);
		env[pos] = newvar;
	}
	return (env);
}
int main(void)
{
	int pos = 0;
	char **py = NULL;
	py = getrealenv();
	printf("%s\n", py[0]);
	printf("%s\n", py[1]);
	printf("%s\n", py[2]);
	printf("%s\n", py[3]);
	py = _setenv("PATH", NULL);
	pos = buscar(py, "PATH");
	printf("%s\n", py[pos]);
	py = _setenv("PATH", "tony:v");
	printf("%s\n", py[pos]);
	getrealenv();
	getrealenv();
	getrealenv();
	getrealenv();
	return (0);
}
