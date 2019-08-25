#include <stdio.h>
#include "holberton.h"

/**
 * getrealenv - get real env.
 *
 * Return: pointer to real env.
 *
 */
char **getrealenv(void)
{
	static int flag = 1;
	static char **cpyenv;
	int i = 0, l = 0, j = 0;

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
/**
*_getenvvar - get environment variable.
* @varname: name of the variable
*
* Return: pointer to environment variable.
*/
char *_getenvvar(char *varname)
{
	char **env = NULL;
	int pos = 0, l = 0, l1 = 0, pe = 0, flag = 0;
	char *var = NULL;

	env = _setenv("PATH", NULL);
	pos =  buscar(env, varname);
	if (pos == -1)
		return (NULL);
	for (; env[pos][l]; l++)
	{
		if (flag)
			l1++;
		if (!flag && env[pos][l] == '=')
		{
			pe = l;
			flag = 1;
		}
	}
	var = _calloc(l1 + 1, sizeof(char));
	for (l1 = 0, pe = pe + 1; env[pos][pe]; l1++, pe++)
		var[l1] = env[pos][pe];
	return (var);
}

/**
* buscar - get environment variable.
* @environ: enviorn
* @varname: name of the variable
*
* Return: position of the variable or -1 if it does not exist
*/
int buscar(char **environ, char *varname)
{
	int i = 0, j = 0, flag = 1;

	while (environ[i])
	{
		if (varname[0] == environ[i][0])
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
/**
 * _setenv - get environment variable.
 * @varname: name of the variable
 * @valor: valor
 * Return: pointer to env
 */
char **_setenv(char *varname, char *valor)
{
	static char **env;
	static char **cpyenv;
	static int flag = 1;
	int i = 0;

	if (flag)
	{
		env = getrealenv();
		flag = 0;
	}
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
		if (pos == -1)
		{
			for (; env[i]; i++)
				;
			cpyenv = _calloc(i + 2, sizeof(char *));
			cpyenv[i + 1] = NULL;
			for (i = 0; env[i]; i++)
				cpyenv[i] = env[i];
			cpyenv[i] = newvar;
			free(env);
			env = cpyenv;
			return (env); }
		free(env[pos]);
		env[pos] = newvar; }
	return (env);
}
