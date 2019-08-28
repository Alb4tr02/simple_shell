#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void imprimir_errores_history(command_t *h)
{
	int l1 = 0;
	char *sp = ": ";
	char *n = NULL;
	char *cont = NULL;
	char *com = NULL;
	char *msg = ": not found";
	char sl = '\n';
	int a = 2;
	com = h->args[0];
	cont = print_number(h->cont);
	n = h->name;
	l1 = _strlen(n);
	write(1, n, l1);
	write(1, sp, 2);
	l1 = _strlen(cont);
	write(1, cont, l1);
	write(1, sp, 2);
	l1 = _strlen(com);
	write(1, com, l1);
	l1 = _strlen(msg);
	write(1, msg, l1);
	write(1, &sl, 1);
	free(cont);
	setstatus(&a);
}

void imprimir_errores_help(command_t *h)
{
	int l1 = 0;
	char *sp = ": ";
	char *n = NULL;
	char *cont = NULL;
	char *com = NULL;
	char *msg = ": not found";
	char sl = '\n';
	int a = 2;
	com = h->args[0];
	cont = print_number(h->cont);
	n = h->name;
	l1 = _strlen(n);
	write(1, n, l1);
	write(1, sp, 2);
	l1 = _strlen(cont);
	write(1, cont, l1);
	write(1, sp, 2);
	l1 = _strlen(com);
	write(1, com, l1);
	l1 = _strlen(msg);
	write(1, msg, l1);
	write(1, &sl, 1);
	free(cont);
	setstatus(&a);
}

void imprimir_errores_cd(command_t *h)
{
	int l1 = 0;
	char *sp = ": ";
	char *n = NULL;
	char *cont = NULL;
	char *com = NULL;
	char *msg = ": not found";
	char sl = '\n';
	int a = 2;
	com = h->args[0];
	cont = print_number(h->cont);
	n = h->name;
	l1 = _strlen(n);
	write(1, n, l1);
	write(1, sp, 2);
	l1 = _strlen(cont);
	write(1, cont, l1);
	write(1, sp, 2);
	l1 = _strlen(com);
	write(1, com, l1);
	l1 = _strlen(msg);
	write(1, msg, l1);
	write(1, &sl, 1);
	free(cont);
	setstatus(&a);
}
