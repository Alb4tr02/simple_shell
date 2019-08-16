#define MAX 1024
#define READING 1
#include "holberton.h"
#include <stdio.h>

/**
 * _getline - function that gets a line from the stdin.
 * @pos: pointer to the actual buffer position.
 * Return: pointer to the buffer that stores the line.
 */
char *_getline(ssize_t *pos)
{
	ssize_t n;
	char *cpy;
	int state;
	size_t size = MAX, aux;
	char *buf = malloc(sizeof(char) * size);

	cpy = buf;
	state = READING;
	//printf("ko:)");
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
	*pos -= 1;
	if (buf[*pos] == '\n')
		*pos -= 1;
	return (cpy);
}
