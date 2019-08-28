#include "holberton.h"
#include <stdio.h>

/**
 * _quote_end - show help document of some functions.
 * @s1: node tha has the builtin command
 *
 * Return: no return
 */

int _quote_end(char *s1)
{
	int i = 0;

	for (; s1[i]; i++)
		if (s1[i] == 39 && !s1[i + 1])
			return (1);
	return (0);
}

/**
 * _concat - show help document of some functions.
 * @args: node tha has the builtin command
 * @pos: position
 * @size: size
 * Return: no return
 */
char *_concat(char **args, int *pos, int size)
{
	char *aux = NULL;
	int cnt = 0, i = 0, tot = 0, j = 0, g = 0;

	cnt  = *pos + 1;
	while (cnt <= size && !_quote_end(args[cnt]))
		cnt++;
	if (!_quote_end(args[cnt]))
		return (NULL);
	for (i = *pos; i <= cnt; i++)
		tot += _strlen(args[i]);
	aux = _calloc(tot, sizeof(char));
	for (i = *pos; i <= cnt; i++)
	{
		for (j = 0; args[i][j]; j++, g++)
			aux[g] = args[i][j];
		aux[g] = ' ';
		g++;
	}
	g--;
	aux[g] = 0;
	*pos = cnt + 1;
	return (aux);
}

/**
 * print_one_alias - show help document of some functions.
 * @name: node tha has the builtin command
 *
 * Return: no return
 */
int print_one_alias(char *name)
{
	alias *aux = NULL;
	char *err = "alias: ";
	char *err1 = " not found\n";
	char eq = '=', sl = 10;

	aux = setalias(NULL);
	aux = buscar_alias(aux, name);
	if (aux)
	{
		write(1, aux->name, _strlen(aux->name));
		write(1, &eq, 1);
		write(1, aux->value, _strlen(aux->value));
		write(1, &sl, 1);
		return (0);
	}
	write(1, err, _strlen(err));
	write(1, name, _strlen(name));
	write(1, err1, _strlen(err1));
	return (-1);
}

/**
 * print_all_alias - show help document of some functions.
 *
 * Return: no return
 */
void print_all_alias(void)
{
	alias *aux = NULL;
	char sl = 10, eq = '=';
	aux = setalias(NULL);

	while (aux)
	{
		write(1, aux->name, _strlen(aux->name));
		write(1, &eq, 1);
		write(1, aux->value, _strlen(aux->value));
		write(1, &sl, 1);
		aux = aux->next;
	}
}

/**
 * _alias - show help document of some functions.
 * @h: node tha has the builtin command
 *
 * Return: 0 or -1
 */
int _alias(command_t *h)
{
	char **args = NULL;
	char **tokens = NULL;
        /*char *aux = NULL;*/
	int pos = 1, i = 0;

	args = h->args;
	for  (; args[i]; i++)
		;
	if (i == 1)
	{
		print_all_alias();
		return (0);
	}
	while (pos < i)
	{
		if (_have_value(args[pos]))
		{
			tokens = token_alias(args[pos]);
			setalias(tokens);
			/*if (_quote_end(args[pos]))
			{
				tokens = token_alias(args[pos]);
				setalias(tokens);
			}
			else
			{
				aux = _concat(args, &pos, i);
				if (aux)
				{
					tokens = token_alias(aux);
					free(aux);
					setalias(tokens);
					free(tokens);
				}
				else
					continue;
			}*/
			free(tokens);
		}
		else
			print_one_alias(args[pos]);
		pos++;
	}
	return (0);
}
