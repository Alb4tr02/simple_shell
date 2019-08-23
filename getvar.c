#include "holberton.h"
#include <stdio.h>
#define MAX 1024
extern char **environ;
char *getvar(char *varname, char *buf)
{
	int i = 0, j = 0, flag = 1, aux = 0;
	while (environ[i])
	{
		if ( varname[0] == environ[i][0] )
		{
			flag = 1, j = 0;
			for (; varname[j]; j++)
				if (varname[j] != environ[i][j])
					flag = 0;
			if (flag && environ[i][j] == '=')
			{
				j++;
				for (; environ[i][j]; aux++, j++)
					buf[aux] = environ[i][j];
				buf[aux] = 0;
				return (buf);
			}
		}
		i++;
	}
	return (NULL);
}
