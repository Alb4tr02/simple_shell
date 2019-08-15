#include "holberton.h"
#include <stdio.h>
int main (void)
{
	ssize_t a = 0;
	ssize_t *p = &a;
	char go[] = "tony";
	char *buf = go;
	buf = _getline(p);

	free(buf);
	return (0);
}
