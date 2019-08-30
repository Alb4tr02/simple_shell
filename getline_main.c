#define MAX 1024
#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * freecommand - free linked list.
 * @h: head node of the linked list.
 *
 * Return: pointer to the new adress of data.
 */
void freecommand(command_t *h)
{
	int i = 0;
	char **args = NULL;

	args = h->args;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(h->name);
	free(args[i]);
	free(args);
	free(h);
}

/**
 * fil_buffer - This fuction creates an array of integers.
 * @buf: pointer that points to the data that will be reallocated.
 * @ct: size of ptr
 * @p: new size of ptr
 * @ch: char
 * @flg: flag
 *
 * Return: pointer to the new adress of data.
 */
void fil_buffer(char *buf, size_t *ct, ssize_t *p, char *ch, int *flg)
{
	char c;
	int flag;
	size_t cnt;
	ssize_t a;

	a = *p;
	cnt = *ct;
	c = *ch;
	flag = *flg;

	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		if (c == 4 && cnt == 0)
			break;
		if (c == '\n' && cnt == 0)
		{
			free(buf);
			return;
		}
		if (c == '\n' && cnt != 0)
		{
			buf[cnt] = 0;
			flag = 0;
			break;
		}
		buf[cnt++] = c;
		a++;
	}
	*p = a;
	*ct = cnt;
	*ch = c;
	*flg = flag;
}

/**
 * check_line - This fuction creates an array of integers.
 * @buf: pointer that points to the data that will be reallocated.
 * @ct: size of ptr
 * @flg: new size of ptr
 *
 * Return: pointer to the new adress of data.
 */
int check_line(char *buf, size_t *ct, int *flg)
{
	char sl;
	size_t cnt;
	int flag;

	flag = *flg;
	cnt = *ct;
	sl = '\n';
	if (cnt == 0 && buf[0] == 0)
	{
		write(STDIN_FILENO, &sl, 1);
		free(buf);
		salir(NULL);
	}
	if (flag)
		write(STDIN_FILENO, &sl, 1);
	if (buf[0] == '\n')
	{
		free(buf);
		return (1);
	}
	return (0);
}
/**
* main - void.
* @argc: number of arguments
* @argv: array of arguments
*
* Return: o if success.
*/
int main(int argc, char **argv)
{
	ssize_t a = 0;
	ssize_t *p = &a;
	command_t *h = NULL;
	size_t cnt = 0;
	char c;
	char *buf = NULL;
	int flag = 1, flag1 = 1;

	getpath();
	if (argc > 1)
	{
		buf = _getline(&a, argv[1]);
		flag1 = 0;
		goto getarg;
	}
	for (; flag1; a = 0, cnt = 0, flag = 1)
	{
		signal(SIGINT, handle_signal);
		prompt();
		buf = _calloc(4096 * 2, 1);
		fil_buffer(buf, &cnt, p, &c, &flag);
		a++;
		if (check_line(buf, &cnt, &flag))
			continue;
getarg:
		buffer_filter(&buf, p);
		h = _getargs(buf, p, argv[0]);
		free(buf);
		if (!h)
			return (0);
		funexc(h);
	}
	return (0);
}
