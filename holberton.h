#ifndef shelly
#define shelly
#include <unistd.h>
#include <stdlib.h>
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
	int (*f)(command_t *h, command_t *copy);
} builtin;

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getline(ssize_t *);
command_t *add_node(command_t **head, char **args, int id);
command_t *_getargs(char *buf, ssize_t *pos);
char **fill_nodes(char *buf, int sp, ssize_t *pos, int *paux);
int clfun(char **arg);
int look(char *fun);
void prompt(void);
void freecommand(command_t *h);
void funexc(command_t *h);
void _extern(command_t *h);
void _built(command_t *h, command_t *copy);
int salir(command_t *h, command_t *copy);
int _history(command_t *h, command_t *copy);
int _env(command_t *h, command_t *copy);
int _help(command_t *h, command_t *copy);
int _cd(command_t *h, command_t *copy);
#endif
