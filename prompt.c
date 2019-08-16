#include "holberton.h"
void prompt(void)
{
        int  y, r, p;
        p = r = y = 0;
        char *prompt = ">:v";
        char *yellow = "\033[1;33m";
        char *reset = "\033[0m";
        for (; reset[r]; r++)
                ;
        for (; yellow[y]; y++)
                ;
        for (; prompt[p]; p++)
                ;
        write(1, yellow, y);
        write(1, prompt, p);
        write(1, reset, r);
}
