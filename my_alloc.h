#ifndef MY_ALLOC_H
#define MY_ALLOC_H

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * struct s_alloc - save ptr address.
 * @ptr: the address of the data.
 * @next: address of next data.
 */

typedef struct s_alloc {
	void *ptr;
	struct s_alloc *next;
}	t_alloc;

void *my_malloc(size_t size);
void my_free(void);

#endif
