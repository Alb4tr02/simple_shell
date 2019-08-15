#ifndef shelly
#define shelly
#include <unistd.h>
#include <stdlib.h>
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getline(ssize_t *);
#endif
