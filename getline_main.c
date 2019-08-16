#include "holberton.h"
#include <stdio.h>
int main (void)
{
	ssize_t a = 0;
	ssize_t *p = &a;
	char go[] = "tony";
	char *buf = go;
	char **args;

	buf = _getline(p);
	args = getargs(buf);
	printf("%s", buf);
	printf("%s", args);
	free(buf);
	return (0);
}
