#ifndef MY_ALLOC_H
#define MY_ALLOC_H

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>


typedef struct s_alloc {
	void *ptr;
	struct s_alloc *next;
}	t_alloc;

void *my_malloc(size_t size);
void my_free(void);

#endif
