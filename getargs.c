#include "holberton.h"
#include <stdio.h>

/**
 * istoken - verfy operators.
 * @c: character to verify
 * Return: 1 if there is coicidence or 0 if it is not
 */
int istoken(char c)
{
	int i = 0;
	char tokens[] = {'&', '|', '\0', '<', '>', ';', -1};

	while (tokens[i++] != -1)
		if (tokens[i] == c)
			return (1);
	return (0);
}

/**
 * _getargs  - create a linked list that contains all arguments.
 * @buf: buffer with the string
 * @pos: pointer tu the actual buffer position
 * Return: a pointer to the linked list
 */
command_t *_getargs(char *buf, ssize_t *pos)
{
	ssize_t p = 0;
	unsigned int flag = 0;
	int sp, id, aux = 0;
	command_t *head;
	char **args;
	int *paux = &aux;

	head = NULL;
	while (p <= *pos)
	{
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
		if (istoken(buf[p]))
		{
			p++;
			p++;
		}
		args = fill_nodes(buf, sp, pos, paux);
		id = clfun(&args[0]);
		add_node(&head, args, id);
	}

	return (head);
}

/**
* fill_nodes - create a linked list that contains all arguments.
* @buf: poiter to pointer to a space in memory
* @sp: size of args
* Return: a pointer to the linked list
*/
char **fill_nodes(char *buf, int sp, ssize_t *pos, int *paux)
{
    char **args = NULL;
    int aux2, s, y, j, i, aux3;

    s = 0;
    aux3 = *paux;
    args = malloc(sizeof(char* ) * (sp + 1));
    *(args + sp) = NULL;
    for (i = 0; sp > 0; sp--, i++)
    {
        aux2 = aux3;
        for (s = 0; buf[aux3] != ' ' && aux3 <= *pos; aux3++, s++)
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
        while (buf[aux3] == ' ' || istoken(buf[aux3]))
            aux3++;
    }
    *paux = aux3;

    return (args);
}
