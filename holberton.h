#ifndef shelly
#define shelly
#include <unistd.h>
#include <stdlib.h>
#define EXT 0
#define BUILT 1
/**
 * struct args - singly linked list
 * @arg: argument
 * @f: pointer to function
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for shell_project
 */
typedef struct command_s
{
	char **args;
	struct command_s *next;
} command_t;

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getline(ssize_t *);
command_t *add_node(command_t **head, char **args);
command_t *_getargs(char *buf, ssize_t *pos);
int clfun(char **arg);
int look(char *fun);
void prompt(void);
#endif
