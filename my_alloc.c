#include "my_alloc.h"

/**
 * free_alloc - free data.
 * @ptr: pointer to the first node in list.
 * Return: no return value.
 */

static void free_alloc(t_alloc *ptr)
{
	if (ptr)
	{
		free_alloc((ptr)->next);
		free((ptr)->ptr);
		free(ptr);
	}
}

/**
 * add_alloc - add new addr in the list.
 * @ptr: the list.
 * @new: the new node.
 * Return: no return value.
 */

static void add_alloc(t_alloc **ptr, t_alloc *new)
{
	if (ptr && new)
	{
		new->next = *ptr;
		*ptr = new;
	}
}

/**
 * save_addr - manage memory.
 * @size: size to alloc.
 * @clear: free data.
 * Return: void * to  the addr.
 */

static void *save_addr(size_t size, bool clear)
{
	static t_alloc *alloc;
	t_alloc *new = NULL;
	char *ptr = NULL;

	if (clear)
	{
		free_alloc(alloc);
		alloc = NULL;
	}
	else if (size)
	{
		ptr = malloc(size);
		if (ptr)
			return (NULL);
		new = malloc(sizeof(t_alloc));
		if (!new)
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

/**
 * my_malloc - alloc new mem.
 * @size: size of mem to alloc.
 * Return: pointer to the mem.
 */

void *my_malloc(size_t size)
{
	return (save_addr(size, false));
}

/**
 * my_free - free all data.
 * Return: no return value.
 */

void my_free(void)
{
	save_addr(0, true);
}

