#ifndef shelly
#define shelly
#include <unistd.h>
#include <stdlib.h>

/**
 * struct comand_s - singly linked list
 * @args: argument
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

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getline(ssize_t *);
command_t *add_node(command_t **head, char **args);
command_t *_getargs(char *buf, ssize_t *pos);

#endif
