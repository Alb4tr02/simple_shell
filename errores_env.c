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
 * imprimir_error_env - compare string.
 * @h: head linked list
 *
 * Return: no return
 */
void imprimir_error_env(command_t *h)
{
	int l1 = 0;
	char *sp = ": ";
	char *com = NULL;
	char *filename = NULL;
	char *msg = ": No such file or directory";
	char sl = '\n';
	int a = 127;

	com = h->args[0];
	filename = h->args[1];
	l1 = _strlen(com);
	write(1, com, l1);
	write(1, sp, 2);
	l1 = _strlen(filename);
	write(1, filename, l1);
	l1 = _strlen(msg);
	write(1, msg, l1);
	write(1, &sl, 1);
	setstatus(&a);
}
/**
 * search_file_env - compare string.
 * @h: head
 *
 * Return: no return
 */
int search_file_env(command_t *h)
{

	char **filename = NULL;
	int n = 0;
	struct stat buf;

	filename = h->args;
	n = stat(filename[1], &buf);
	printf("%d", n);
	if (n == -1)
		imprimir_error_env(h);
	return (0);
}
/**
 * imprimir_error_setenv - compare string.
 * @h: string 1
 *
 * Return: no return
 */
void imprimir_error_setenv(command_t *h)
{
	int l1 = 0;
	char *sp = ": ";
	char *com = NULL;
	char *variable = NULL;
	char *msg = ": Variable not found";
	char sl = '\n';
	int a = 1;

	com = h->args[0];
	variable = h->args[1];
	l1 = _strlen(com);
	write(1, com, l1);
	write(1, sp, 2);
	l1 = _strlen(variable);
	write(1, variable, l1);
	l1 = _strlen(msg);
	write(1, msg, l1);
	write(1, &sl, 1);
	setstatus(&a);
}
/**
 * imprimir_error_unsetenv - compare string.
 * @h: head
 *
 * Return: no return
 */
void imprimir_error_unsetenv(command_t *h)
{
	int l1 = 0;
	char *sp = ": ";
	char *com = NULL;
	char *variable = NULL;
	char *msg = ": Variable not found";
	char sl = '\n';
	int a = 1;

	com = h->args[0];
	variable = h->args[1];
	l1 = _strlen(com);
	write(1, com, l1);
	write(1, sp, 2);
	l1 = _strlen(variable);
	write(1, variable, l1);
	l1 = _strlen(msg);
	write(1, msg, l1);
	write(1, &sl, 1);
	setstatus(&a);
}
