#include "holberton.h"

/**
 * _realloc - This fuction creates an array of integers.
 * @ptr: pointer that points to the data that will be reallocated.
 * @old_size: size of ptr
 * @new_size: new size of ptr
 * Return: pointer to the new adress of data.
 *
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newp;
	unsigned int a = 0;
	unsigned int b = 0;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && (ptr != NULL))
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		newp = malloc(new_size);
		free(ptr);
		return (newp);
	}
	newp =  malloc(new_size);
	if (newp == NULL)
		return (NULL);
	for (; (a <= new_size) && (b <= old_size); a++, b++)
		*((char *)newp + a) =  *((char *)ptr + b);
	free(ptr);
	return (newp);
}
