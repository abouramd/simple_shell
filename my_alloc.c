#include "my_alloc.h"

static void free_alloc(t_alloc **ptr)
{
	if (ptr && *ptr)
	{
		free_alloc(&(*ptr)->next);
		free((*ptr)->ptr);
		free(*ptr);
		*ptr = NULL;
	}
}

static void add_alloc(t_alloc **ptr, t_alloc *new)
{
	if (ptr && new)
	{
		new->next = *ptr;
		*ptr = new;
	}
}

static void *save_addr(size_t size, bool clear)
{
	static t_alloc *alloc;
	t_alloc *new = NULL;
	char *ptr = NULL;

	if (clear)
		free_alloc(&alloc);
	else if (size)
	{
		if (!(ptr = malloc(size)))
			return (NULL);
		if (!(new = malloc(sizeof(t_alloc))))
		{
			free(ptr);
			return (NULL);
		}
		new->ptr = ptr;
		add_alloc(&alloc, new);
		while (size--)
			ptr[size] = 0;
	}
	return (ptr);
}

void *my_malloc(size_t size)
{
	return (save_addr(size, false));
}

void my_free(void)
{
	save_addr(0, true);
}

/* int main(void)
{
	my_malloc(1000);
	my_malloc(1000);
	my_malloc(1000);
	my_malloc(1000);
	my_free();
	return EXIT_SUCCESS;
} */
