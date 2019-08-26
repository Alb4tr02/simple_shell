#ifndef shelly
#define shelly
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define EXT 0
#define BUILT 1

/**
 * struct command_s - singly linked list
 * @args: argument
 * @id: id token (0- intern or 1 - extern)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for shell_project
 */
typedef struct command_s
{
	char **args;
	int id;
	struct command_s *next;
} command_t;

/**
* struct builtins - type of builtins
*
* @built: command
* @f: the function assoiated
*/
typedef struct builtins
{
	char *built;
	int (*f)(command_t *h);
} builtin;

/**
* struct builtins - type of builtins
*
* @built: command
* @f: the function assoiated
*/
typedef struct aliases
{
	char *name;
	char *value;
	struct aliases *next;
} alias;
int have_alias(char *buf, int i);
void buffer_filter(char **buffer, ssize_t *p);
void _replacealias(alias *ali, char *newbuf, int *pos);
alias *_isalias(char *buf, int *i);
void _ignorecomments(char *buf, int *i);
void _replacevar(char *buf, char *newbuf, int *i, int *pos);
int _isespcialchr(char c);
int istoken(char c);
void print_all_alias(void);
int print_one_alias(char *name);
int _strcmp(char *s1, char *s2);
alias *setalias(char **tokens);
alias *buscar_alias(alias *head, char *name);
int _have_value(char *arg);
char **token_alias(char *alias);
int _quote_end(char *s1);
char *_concat(char **args, int *pos,int size);
int _alias(command_t *h);
alias *add_alias(alias **head, char *name, char *value);
int _setenviron(command_t *h);
int _unsetenv(command_t *h);
int _strlen(char *str);
char  *getvaderdir(void);
int chtopreviousdir(void);
char *_getenvvar(char *varname);
char **_setenv(char *varname, char *valor);
int buscar(char **environ, char *varname);
char **getrealenv(void);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *_calloc(unsigned int nmemb, unsigned int size);
char *_getline(ssize_t *pos, char *pathname);
command_t *add_node(command_t **head, char **args, int id);
command_t *_getargs(char *buf, ssize_t *pos);
char **fill_nodes(char *buf, int sp, ssize_t *pos, int *paux);
int clfun(char **arg);
int look(char *fun);
void prompt(void);
int _readandcpy(char *fr, char *to, char *buf);
char *getvar(char *varname, char *buf);
void freecommand(command_t *h);
void getentorno(void);
void funexc(command_t *h);
void _extern(command_t *h);
void _built(command_t *h);
int salir(command_t *h);
int _history(command_t *h);
int _env(command_t *h);
int _help(command_t *h);
int _cd(command_t *h);
#endif
