#include "pars.h"
#include "shell.h"

/**
 * string_size - count string size.
 * @ptr: the string.
 * Return: size of the string.
 */

size_t string_size(t_string *ptr)
{
	if (!ptr)
		return (0);
	return (string_size(ptr->next) + 1);
}

/**
 * convert_string - t_string to char *.
 * @s: t_string data.
 * Return: char * content the string data.
 */

char *convert_string(t_string *s)
{
	char *str;
	size_t size;
	size_t index = 0;
	char qout = 0;

	size = string_size(s);
	str = my_malloc(sizeof(char) * (size + 1));
	if (!str)
		return (str);
	while (s)
	{
		if (!qout && (s->c == '"' || s->c == '\''))
			qout = s->c;
		else if (qout == s->c)
			qout = 0;
		else
			str[index++] = s->c;
		s = s->next;
	}
	str[index] = 0;
	return (str);
}