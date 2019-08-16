#include "holberton.h"
#include <stdio.h>
int istoken(char c)
{
	int i = 0;
	char tokens[] = {'&', '|', '\0', '<', '>', -1};
	while (tokens[i++] != -1)
		if (tokens[i] == c)
			return (1);
	return (0);
}
command_t *_getargs(char *buf, ssize_t *pos)
{
	ssize_t aux, aux2, p = 0;
	unsigned int size = 0, flag = 0;
	int sp, s, i, y, j;
	command_t *head;
	head = NULL;
	while (p <= *pos)
	{
		aux = p;
		sp = 0;
		flag = 1;
		while (!istoken(buf[p]) && p <= *pos)
		{
			if (p == *pos && buf[p] != ' ')
				sp++;
			if (buf[p] == ' ')
			{
				if (flag)
					sp++;
				flag = 0;
			}
			else
				flag = 1;
			p++;
		}
		if (p != 0 && sp == 0)
			sp++;
		char **args = malloc(sizeof(char *) * (sp + 1));
		*(args + sp) = NULL;
		for (i = 0; sp > 0; sp--, i++)
		{
			aux2 = aux;
			for (s = 0; buf[aux] != ' ' && aux <= *pos; aux++, s++)
				;
			args[i] = malloc(sizeof(char) * (s + 1));
			if (!args[i])
			{
				for (y = 0; y < i; y++)
					free(args[y]);
				free(args);
				return (NULL);
			}
			for (j = 0; j < s; j++, aux2++)
				*(*(args + i) + j) = buf[aux2];
			*(*(args + i) + s) = 0;
			if (i == 0)
				clfun(&(args[i]));
			while (buf[aux] == ' ')
				aux++;
		}
		add_node(&head, args);
	}

	return (head);
}
