#define MAX 10
#define READING 1
#define NOTREADING 0
#include "holberton.h"
#include <stdio.h>
char *_getline(ssize_t *pos)
{
	ssize_t n;
	char *cpy;
	int state;
	size_t size = MAX, aux;
	char *buf = malloc(sizeof(char) * size);
	cpy = buf;
	state = READING;
	while (state)
	{
		if (!buf)
			return (NULL);
		n = read(STDIN_FILENO, buf, MAX);
		*pos += n;
		if (n == -1)
		{
			free(buf);
			return (NULL);
		}
		if (n != MAX)
			break;
		else if (n == MAX)
		{
			if (buf[*pos - 1] == 10)
				break;
			aux = size;
			size += size;
			buf = (char *)_realloc(buf, aux, size);
			cpy = buf;
			buf += aux;
		}
	}
	return (cpy);
}
