#include "holberton.h"
int _isespecialchr(char c)
{
	int i = 0;
        char tokens[] = {'&', '|', '\0', ';', '\n', '#', '$', ' ', '\t',  -1};
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
		if(buf[st] == '\n' || buf[st] == 0
		   || buf[st] == ';' || buf[st] == '&'
			|| buf[st] == '|')
			break;
		st--;
	}
	if (st < 0)
		st++;
	for(; st <= end; st++)
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
void _replacevar(char *buf, char *newbuf, int *i, int *pos)
{
	char *name = _calloc(60, 1);
	char *value = NULL;
	int cb = *i, j = 0;
	cb++;
	if (buf[cb] == '$' || buf[cb] == '?')
	{
		int a = setstatus(NULL);
		char *stat = print_number(a);
		int j = 0;
		for (; stat[j]; j++, *pos = *pos + 1)
			newbuf[*pos] = stat[j];
		*pos = *pos + 1;
		free(stat);
		cb++;
		*i = cb;
		free(name);
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
	char *newbuf = _calloc(500, 1);
	alias *ali = NULL;
	char *buf = *buffer;
	int pos = 0, i = 0, cpy = 0;
	while (i <= *p)
	{
		if (buf[i] == '#')
		{
			_ignorecomments(buf, &i);
			continue;
		}
		if (buf[i] == '$')
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
		newbuf[pos] = buf[i];
		i++, pos++;
	}
	free(buf);
	*p = pos;
	*buffer = newbuf;
}
