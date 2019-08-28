#include "holberton.h"
#include <stdio.h>

/**
 * add_alias - add alias.
 * @head: node tha has the builtin command
 * @name: name
 * @value: value
 * Return: no return
 */
alias *add_alias(alias **head, char *name, char *value)
{
	int flag = 1;
	alias *p = *head;
	alias *new = malloc(sizeof(alias));
	alias *cpy = NULL;

	cpy = buscar_alias(p, name);
	if (cpy)
	{
		free(cpy->value);
		free(name);
		free(new);
		cpy->value = value;
		return (cpy);
	}
	do {
		if (!p || !(p->next))
		{
			if (!new)
				return (NULL);
			new->name = name;
			new->value = value;
			new->next = NULL;
			if (!p)
			{
				*head = new;
				return (new);
			}
			p->next = new;
			flag = 0;
		}
		else
			p = p->next;
	} while (flag);
	return (new);
}

/**
 * _strcmp - compare string.
 * @s1: string 1
 * @s2: string 1
 * Return: no return
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0, j = 0;
	for (; s1[i] && s2[j]; i++, j++)
		if (s1[i] != s2[j])
			return (0);
	if (!s1[i] && !s2[j])
		return (1);
	return (0);
}
/**
 * buscar_alias - buscar alias
 * @head: head
 * @name: name
 *
 * Return: no return
 */
alias *buscar_alias(alias *head, char *name)
{
	char *cpyname = NULL;

	while (head)
	{
		cpyname = head->name;
		if (_strcmp(cpyname, name))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * setalias - set alias.
 * @tokens: node tha has the builtin command
 *
 * Return: no return
 */
alias *setalias(char **tokens)
{
	static alias *head;
	char *name = NULL, *value = NULL;
	alias *res = NULL;
	static int flag = 1;

	if (!tokens)
		return (head);
	else
	{
		name = tokens[0];
		value = tokens[1];
	}
	if (flag && !value)
		return (head);
	if (name && !value)
	{
		res = buscar_alias(head, name);
		return (res);
	}
	if (!name && !value)
	{
		return (head);
	}
	if (name && value)
	{
		res = add_alias(&head, name, value);
		return (res);
	}
	return (NULL);
}

/**
 * _strlen - longitud string.
 * @str: pointer to string
 *
 * Return: size
 */
int _strlen(char *str)
{
	int i = 0;
	if (str)
	{
		for (; str[i]; i++)
			;
		return (i + 1);
	}
	return (-1);
}

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
	char *err = "alias: ";
	char *err1 = " not found";
	int l = 0,  st = 127, sl = 10;;

	l = _strlen(err);
	write(1, err, l);
	l = _strlen(name);
	write(1, name, l);
	l = _strlen(err1);
	write(1, err1, l);
	write(1, &sl, 1);
	setstatus(&st);
	return;
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
char *_concat(char **args, int *pos,int size)
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
	aux = setalias(NULL);
	aux = buscar_alias(aux, name);
	if (aux)
	{
		printf("%s=%s\n", aux->name, aux->value);
		return (0);
	}
	print_error_alias(name);
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
	aux = setalias(NULL);
	while (aux)
	{
		printf("%s=%s\n", aux->name, aux->value);
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
	char **args = NULL, **tokens = NULL;
	char *aux = NULL;
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
			if (_quote_end(args[pos]))
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
				continue;
			}
			free(tokens);
		}
		else
			print_one_alias(args[pos]);
		pos++;
	}
	return (0);
}
