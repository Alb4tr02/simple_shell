#include "holberton.h"
#include <stdio.h>
#define MAX 1024
char *getvar(char *varname, char *buf)
{
	ssize_t p = 0;
	int i = 0, pvar = 0, flag = 1;
	int j = 0, c1 = 0, c2 = 0;
	char *name = "/environ";
	char *pathname = NULL;
	char *env = NULL;
	char buffer[MAX];
	pathname = getcwd(buffer, MAX);
	for (; pathname[c1]; c1++)
		;
	for (; name[c2]; c2++, c1++)
		pathname[c1] = name[c2];
	pathname[c1] = 0;
	env = _getline(&p, pathname);
	for (; i <= p; i++)
	{
		pvar = 0;
		if (env[i] == varname[pvar] && env[i - 1] == '\n')
		{
			flag = 1;
			for (; varname[pvar]; pvar++, i++)
				if (varname[pvar] != env[i])
					flag = 0;
			if (flag && env[i] == '=')
			{
				i++;
				for (; env[i] != '\n'; i++, j++)
					buf[j] = env[i];
				buf[j] = 0;
				break;
			}
		}
	}
	return (buf);
}
