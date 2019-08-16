#ifndef shelly
#define shelly
#include <unistd.h>
#include <stdlib.h>

/**
 * struct args - singly linked list
 * @arg: argument
 * @f: pointer to function
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for shell_project
 */
typedef struct args
{
	char *arg;
	char *func;
	struct args *next;
} args
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getline(ssize_t *);
char **_getargs(char *buf);
list_t *add_node(list_t **head, const char *str);
#endif
