#ifndef shelly
#define shelly
#include <unistd.h>
#include <stdlib.h>
<<<<<<< HEAD

=======
>>>>>>> b195efcdec08fdcad857354d3d4ae42d1c3b2ec2
/**
 * struct args - singly linked list
 * @arg: argument
 * @f: pointer to function
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for shell_project
 */
<<<<<<< HEAD
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
=======
typedef struct command_s
{
	char **args;
	struct command_s *next;
} command_t;

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getline(ssize_t *);
command_t *add_node(command_t **head, char **args);
command_t *_getargs(char *buf, ssize_t *pos);
>>>>>>> b195efcdec08fdcad857354d3d4ae42d1c3b2ec2
#endif
