#define MAX 4096
#define READING 1
#include "holberton.h"
#include <stdio.h>
#include <signal.h>
/**
 * _getline - function that gets a line from the stdin.
 * @pos: pointer to the actual buffer position.
 * Return: pointer to the buffer that stores the line.
 */
char *_getline(ssize_t *pos, char *pathname)
{
	int fd = 0;
	ssize_t n = 0;
	char *cpy = NULL;
	int state = 0;
	size_t size = MAX, aux = 0;
	char *buf = NULL;
	int flag = 1;
	int cnt = 0;
	char c;

	if (pathname == NULL)
		fd = STDIN_FILENO, size = 100;
	else
		fd = open(pathname, O_RDONLY);
	buf = _calloc(size * 4, size);
	buf[size -1] = 0;
	buf[0] = 0;
	cpy = buf;
	state = READING;
	while (state)
	{
		if (!buf)
			return (NULL);
		n = read(fd, buf, MAX);
		*pos += n;
		if (buf[0] == 0)
			break;
		if (n == -1)
		{
			free(buf);
			return (NULL);
		}
		if (n != MAX && buf[*pos - 1] == '\n')
			break;
		else
		{
			buf += n;
			while(read(STDIN_FILENO, &c, 1) == 1 && cnt < (int)size)
			{
				if (c == 4 && cnt == 0)
					exit(0);
				if(c == '\n')
				{
					buf[cnt - 1] = '\n';
					return (buf);
				}

				buf[cnt] = c;
				*pos = *pos + 1;
				cnt++;
			}
		}
		if (n == MAX)
		{
			if (buf[*pos - 1] == 10)
				break;
			aux = size;
			size += size;
			buf = (char *)_realloc(buf, aux, size);
			cpy = buf;
			buf += aux;
			flag = 0;
		}
	}
	*pos -= 1;
	if (buf[*pos] == '\n')
		*pos -= 1;
	if (flag)
		return (buf);
	return (cpy);
}
