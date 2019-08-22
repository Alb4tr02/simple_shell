#define MAX 1024
#include "holberton.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
void freecommand(command_t *h)
{
        int i = 0;
        char **args;
        args = h->args;
        while (args[i])
        {
                free(args[i]);
                i++;
        }
        free(args[i]);
        free(args);
        free(h);
}
int main (void)
{
	int status;
        ssize_t a = 0;
        ssize_t *p = &a;
        char *buf = NULL;
        command_t *h;
        command_t *cpy;
	getentorno();
        while (1)
        {
                status = 0;
                a = 0;
                prompt();
                buf = _getline(p, NULL);
                if (buf[0] == '\n')
                {
                        free (buf);
                        continue;
                }
                h = _getargs(buf, p);
                if (buf[0] == '*')
                {
                        freecommand(h);
                        free(buf);
                        return (0);
                }
                if (!h)
                        return (0);
                while (h != NULL)
                {
                        cpy = h;
                        if (!h->args)
                                printf("no sirve esta mierda\n");
                        if (fork() == 0)
                        {
                                status = execve(*h->args, h->args, NULL);
                        }
                        else
                                wait(NULL);
                        if (status == -1)
                        {
                                printf("Error.\n");
                        }
                        h = h->next;
                        freecommand(cpy);
                }
		free(buf);
        }
        return (0);

}
