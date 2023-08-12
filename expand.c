#include "pars.h"
#include "shell.h"
#include <_ctype.h>
#include <ctype.h>

char *get_id(t_string **str)
{
	t_string	*save = (*str);
	t_string	*tmp;
	char		*s;
		
	while ((*str)->next && (isalpha((*str)->next->c) || isnumber((*str)->next->c) || (*str)->next->c == '_'))
		(*str) = (*str)->next;
	tmp = (*str)->next;
	(*str)->next = NULL;
	s = convert_string(save);
	(*str) = tmp;
	return (s);
}

void replace_value(t_string **new, t_string **str)
{
	(*str) = (*str)->next;
	if (!*str)
		new_string(new, '$');
	else if ((*str)->c == '?')
	{
		new_string(new, '<');
		new_string(new, 'E');
		new_string(new, '>');	
		(*str) = (*str)->next;
	}
	else if ((*str)->c == '$')
	{
		new_string(new, '<');
		new_string(new, 'P');
		new_string(new, '>');
		(*str) = (*str)->next;
	}
	else if (isalpha((*str)->c) || (*str)->c == '_')
	{
		int i = 0;
		char *id = get_id(str);
		char *value = find_env(id);
		while (value && *value)
			new_string(new, *(value++));
	}
}


t_string *change_value(t_string *str)
{
	char qout = 0;
	t_string *new = NULL;

	while (str)
	{
		if (!qout && (str->c == '"' || str->c == '\''))
			qout = str->c;
		else if (qout == str->c)
			qout = 0;
		if (qout != '\'' && str->c == '$')
		{
			replace_value(&new, &str);
			continue;
		}
		else
			new_string(&new, str->c);
		str = str->next;
	}
	return (new);
}

t_string *expand(t_string *str)
{
	return (change_value(str));
}
