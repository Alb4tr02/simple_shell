#include <stdlib.h>
#include "holberton.h"

/**
 * _calloc - This fuction allocates memory using malloc
 * @nmemb: number of elements.
 * @size: size in bytes of each element.
 * Return: pointer to the espace reserved.
 *
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *p;
	int limit = 0;
	int i = 0;

	if (nmemb == 0 || size == 0)
		return (NULL);
	p = malloc(size * nmemb);

	limit = size * nmemb;
	if (p == NULL)
		return (NULL);
	for (i = 0; i < limit; i++)
		*((char *)p + i) = 0;
	return (p);
}
