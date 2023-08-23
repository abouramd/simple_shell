#include "pars.h"
#include "shell.h"
#include <ctype.h>
#include <unistd.h>

char *get_id(t_string **str)
{
	t_string	*save = (*str);
	t_string	*tmp;
	char		*s;
		
	while ((*str)->next && (isalpha((*str)->next->c) || ((*str)->next->c <= '9' && (*str)->c >= '0') || (*str)->next->c == '_'))
		(*str) = (*str)->next;
	tmp = (*str)->next;
	(*str)->next = NULL;
	s = convert_string(save);
	(*str) = tmp;
	return (s);
}

void replace_value(t_string **new, t_string **str, t_env *env, int e)
{
	(*str) = (*str)->next;
	if (!*str)
		new_string(new, '$');
	else if ((*str)->c == '?')
	{
		char *s = itoa(e);/* replace 255 with the exit status */
		while (s && *s)
			new_string(new, *(s++));
		(*str) = (*str)->next;
	}
	else if ((*str)->c == '$')
	{
		char *s = itoa(getpid());
		while (s && *s)
			new_string(new, *(s++));
		(*str) = (*str)->next;
	}
	else if (isalpha((*str)->c) || (*str)->c == '_')
	{
		char *id = get_id(str);
		char *value = find_env_p(id, env);
		while (value && *value)
			new_string(new, *(value++));
	}
}


t_string *change_value(t_string *str, t_env *env, int e)
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
			replace_value(&new, &str, env, e);
			continue;
		}
		else
			new_string(&new, str->c);
		str = str->next;
	}
	return (new);
}

t_string *expand(t_string *str, t_env *env, int e)
{
	return (change_value(str, env, e));
}
