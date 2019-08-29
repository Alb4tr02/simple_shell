#include "holberton.h"
#include <sys/types.h>
#include <sys/wait.h>

int _isespecialchr(char c)
{
	int i = 0;
	char tokens[] = { '$', '|', '\0', ';', '\n', '#', '$', ' ', '\t',  -1};

	while (tokens[i] != -1)
	{
		if (tokens[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int have_alias(char *buf, int i)
{
	int st = i - 1;
	int end = i;
	int cnt = 0, flag = 0;
	char *al = "alias";

	if (st < 0)
		return (0);
	while (st >= 0)
	{
		if (buf[st] == '\n' || buf[st] == 0
		   || buf[st] == ';' || buf[st] == '&'
			|| buf[st] == '|')
			break;
		st--;
	}
	if (st < 0)
		st++;
	for (; st <= end; st++)
	{
		if (buf[st] == 'a')
		{
			for (cnt = 0; al[cnt]; cnt++, st++)
			{
				if (al[cnt] != buf[st])
					break;
				if (!al[cnt + 1] && (buf[st + 1] == ' ' ||
							buf[st + 1] == '\t'
							|| buf[st + 1] == '$'))
					flag = 1;
			}
		}
	}
	return (flag);
}
int replace_stat(char *buf, char *newbuf, int *i, int *pos)
{
	int a, j, p;
	char *stat;

	(void)buf;
	(void)i;
	a = 0, j = 0;
	stat = print_number(a);
	p = *pos;
	a = setstatus(NULL);
	for (; stat[j]; j++, p = p + 1)
		newbuf[p] = stat[j];
	p = p + 1;
	free(stat);
	return (p);
}
int replace_pid(char *buf, char *newbuf, int *i, int *pos)
{
	int a = getpid();
	char *stat = print_number(a);
	int j = 0;
	int p;
	p = *pos;
	(void)buf;
	(void)i;
	for (; stat[j]; j++, p++)
		newbuf[p] = stat[j];
	p++;
	free(stat);
	return (p);
}
void _replacevar(char *buf, char *newbuf, int *i, int *pos)
{
	char *name = _calloc(60, 1);
	char *value = NULL;
	int cb = *i, j = 0, p = 0;
	cb++;
	if (buf[cb] == '$' || buf[cb] == '?')
	{
		if (buf[cb] == '$')
			p = replace_pid(buf, newbuf, i, pos);
		else
			p = replace_stat(buf, newbuf, i, pos);
		cb++;
		*i = cb;
		*pos = p - 1;
		return;
	}
	else
	{
		for (; !_isespecialchr(buf[cb]); cb++)
			;
		for (; (j + 1 + *i) < cb; j++)
			name[j] = buf[j + *i + 1];
	}
	value = _getenvvar(name);
	if (value)
	{
		for (j = 0; value[j]; j++, *pos = *pos + 1)
			newbuf[*pos] = value[j];
		free(value);
	}
	free(name);
	*i = cb;
}
void _ignorecomments(char *buf, int *i)
{
	/*if (*i != 0)
	{
		if (buf[*i - 1] != ' ' && buf[*i - 1] != '\t')
			*i = *i + 1;
			return;
	}*/
	while(buf[*i] != 0 && buf[*i] != '\n')
		*i = *i + 1;
	*i = *i + 1;
}
alias *_isalias(char *buf, int *i)
{
	alias *ali =  NULL;
	int cb = *i, j = 0;
	char *name = NULL;
	if (cb != 0 && !_isespecialchr(buf[(cb - 1)]))
		return (NULL);
	name = _calloc(500, 1);
	for (; !_isespecialchr(buf[cb]); cb++)
		;
	for (; (j + *i) < cb; j++)
		name[j] = buf[j + *i];
	ali = setalias(NULL);
	ali = buscar_alias(ali, name);
	free(name);
	if (ali)
	{
		*i = cb;
		return (ali);
	}
	return (NULL);
}
void _replacealias(alias *ali, char *newbuf, int *pos)
{
	int i = 0;
	char *value = NULL;
	value = ali->value;
	while (value[i])
	{
		if (value[i] != 39)
		{
			newbuf[*pos] = value[i];
			*pos = *pos + 1;
		}
		i++;
	}
}
void buffer_filter(char **buffer, ssize_t *p)
{
	char *newbuf = _calloc(4096 * 2, 1);
	alias *ali = NULL;
	char *buf = *buffer;
	int pos = 0, i = 0, cpy = 0;
	while (i <= *p)
	{
		if (buf[i] == '#')
		{
			if (i == 0)
			{
				_ignorecomments(buf, &i);
				continue;
			}
			else if (buf[i - 1] == ' ' || buf[i - 1] == '\t' ||
				 buf[i - 1] == ';')
			{
				_ignorecomments(buf, &i);
				continue;
			}
		}
		if (buf[i] == '$' && buf[i + 1] != ' '&& buf[i + 1] != '\t'
		    && buf[i + 1] != 0 && buf[i + 1] != '\n'
		    && buf[i + 1] != ';' )
		{
			_replacevar(buf, newbuf, &i, &pos);
			continue;
		}
		cpy = i;
		ali = _isalias(buf, &i);
		if (ali)
		{
			if (!have_alias(buf, i))
			{
				_replacealias(ali, newbuf, &pos);
				continue;
			}
			i = cpy;
		}
		i = cpy;
		newbuf[pos] = buf[i];
		i++, pos++;
	}
	free(buf);
	*p = pos;
	*buffer = newbuf;
}
