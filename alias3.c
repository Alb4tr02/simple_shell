#include "holberton.h"
#include <stdio.h>

/**
 * _have_value - valueof alias.
 * @arg: pointer to arg
 *
 * Return: 0 or-1
 */
int _have_value(char *arg)
{
	int i = 0;

	if (arg)
	{
		for (; arg[i]; i++)
			if (arg[i] == '=')
				return (1);
		return (0);
	}
	return (-1);
}

/**
 * print_error_alias - show help document of some functions.
 * @name: node tha has the builtin command
 *
 * Return: no return
 */
void print_error_alias(char *name)
{
	char *err = NULL;
	char *err1 = NULL;
	int l = 0,  st = 127, sl = 10;

	err = "alias: ";
	err1 = " not found";
	l = _strlen(err);
	write(1, err, l);
	l = _strlen(name);
	write(1, name, l);
	l = _strlen(err1);
	write(1, err1, l);
	write(1, &sl, 1);
	setstatus(&st);
}

/**
 * token_alias - show help document of some functions.
 * @alias: node tha has the builtin command
 *
 * Return: no return
 */
char **token_alias(char *alias)
{
	char **tokens = NULL;
	int i = 0, pos = 0, l = 0, lv = 0;

	tokens = _calloc(2, sizeof(char *));
	for (; alias[pos]; pos++)
		if (alias[pos] == '=')
			break;
	if (pos == 0)
	{
		tokens[0] = _calloc(2, 1);
		tokens[0][0] = '=';
		tokens[1] = _calloc(3, 1);
		tokens[1][0] = 39;
		tokens[1][1] = 39;
		return (tokens);
	}
	l = _strlen(alias);
	lv = l - 2 - pos;
	tokens[0] =  _calloc(pos + 1, sizeof(char));
	tokens[1] = _calloc(lv + 1, sizeof(char));
	for (i = 0; i < pos; i++)
		tokens[0][i] = alias[i];
	pos++;
	for (i = 0; i < lv; i++)
		tokens[1][i] = alias[pos + i];
	return (tokens);
}
