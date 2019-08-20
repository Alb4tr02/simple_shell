#include "holberton.h"
#define MAX 4096
void movbuf(char *buf, int offs, ssize_t pos, int stp)
{
	int start = 0;
	if (offs > 0)
	{
		for (; pos >= stp; pos--)
			buf[pos + offs] = buf[pos];
	}
	if (offs < 0)
	{
		start = stp + offs;
		offs *= -1;
		for (; start <= pos - offs; start++)
			buf[start] = buf[start + offs];
	}
}
void actenv(char *varname, char *valor)
{
	ssize_t p = 0;
	int i = 0, pos = 0, offs = 0, pvar = 0, flag = 1;
	int j = 0, k = 0, c1 = 0, c2 = 0, fd = 0, lv = 0, vact = 0;
	char *name = "/environ";
	char *pathname = NULL;
	char *env = NULL;
	char buffer[MAX];
	pathname = getcwd(buffer, MAX);
	for (; varname[j]; j++)
		;
	for (; valor[k]; k++)
		;
	k++;
	valor[k] = '\n';
	for (; pathname[c1]; c1++)
		;
	for (; name[c2]; c2++, c1++)
		pathname[c1] = name[c2];
	pathname[c1] = 0;
	env = _getline(&p, pathname);
	for (; i <= p; i++;)
	{
		pvar = 0;
		if (env[i] == varname[pvar])
		{
			flag = 1;
			for (; varname[pvar]; pvar++, i++)
				if (varname[pvar] != env[i])
					flag = 0;
			if (flag && env[i + 1] == '=')
			{
				pos = i + 1;
				i += 2;
				for (; env[i] != '\n'; i++, vact++)
					;
				vact++;
				offs = k - vact;
				break;
			}
		}
	}
	movbuf(env, offs, p, i);
	
}
