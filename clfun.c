#include "holberton.h"
#include <stdio.h>
int look(char *fun)
{
	int pos = 0, flag = 0, i = 0;
	char *current;
	char *built[] =  {"history", "exit", "env", "help", NULL};
	while (built[i])
	{
		current = built[i];
		for (pos = 0; current[pos] && fun[pos]; pos++)
		{
			if (current[pos] == fun[pos])
			{
				if (current[pos + 1] == 0 && fun[pos +1] == 0)
					return (BUILT);
			}
			else
				break;
		}
		i++;
	}
	return ((flag == 0) ? EXT: BUILT);
}
int  clfun(char **arg)
{
	char *PATH = "/bin/";
	unsigned int sa = 0, sp = 0;
	int end = 0, res;
	if (*(*(arg + 0) + 0) == '/')
		return (EXT);
	res = look(*(arg + 0));
	for (; PATH[sp]; sp++)
		;
	for (; *(*(arg + 0) + sa); sa++)
		;
	sa++;
	*arg = _realloc(*arg, sa, sa + sp);
	if (!*arg)
		return (-1);
	end = sa + sp - 1;
	for (; sa > 0; sa--, end--)
		*(*(arg + 0) + end) = *(*(arg + 0) + sa - 1);
	for (end = 0; PATH[end]; sp--, end++)
		*(*(arg + 0) + end) = PATH[end];
	return (res);
}
