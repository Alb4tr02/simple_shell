#include "holberton.h"

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
		/*res = buscar_alias(head, value);
		if (res)
			res = add_alias(&head, name, res->value);
		else*/
			res = add_alias(&head, name, value);
		return (res);
	}
	return (NULL);
}
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
		return (NULL);
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
int _quote_end(char *s1)
{
	int i = 0;
	for (; s1[i]; i++)
		if (s1[i] == 39 && !s1[i + 1])
			return (1);
	return (0);
}
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
int print_one_alias(char *name)
{
	alias *aux = NULL;
	char *err = "alias: ";
	char *err1 = " not found\n";
	char eq = '=', sl = 10, qu = 39;
	aux = setalias(NULL);
	aux = buscar_alias(aux, name);
	if (aux)
	{
		write(1, aux->name, _strlen(aux->name) - 1);
		write(1, &eq, 1);
		write(1, &qu, 1);
		write(1, aux->value, _strlen(aux->value) - 1);
		write(1, &qu, 1);
		write(1, &sl, 1);
		return (0);
	}
	write(1, err, _strlen(err));
	write(1, name, _strlen(name));
	write(1, err1, _strlen(err1));
	return (-1);
}
void print_all_alias(void)
{
	alias *aux = NULL;

	aux = setalias(NULL);
	while (aux)
	{
		print_one_alias(aux->name);
		/*write(1, aux->name, _strlen(aux->name));
		write(1, &eq, 1);
		write(1, aux->value, _strlen(aux->value));
		write(1, &sl, 1);*/
		aux = aux->next;
	}
}
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
