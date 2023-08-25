#include "pars.h"
#include "shell.h"
#include <ctype.h>
#include <unistd.h>

/**
 * get_id - get the id of the var
 * @str: the data o var
 * Return: the string content var name
 */

char *get_id(t_string **str)
{
	t_string	*save = (*str);
	t_string	*tmp;
	char		*s;

	while ((*str)->next
	&& (isalpha((*str)->next->c)
	|| ((*str)->next->c <= '9'
	&& (*str)->c >= '0')
	|| (*str)->next->c == '_'))
		(*str) = (*str)->next;
	tmp = (*str)->next;
	(*str)->next = NULL;
	s = convert_string(save);
	(*str) = tmp;
	return (s);
}

/**
 * replace_value - replace the value of the var name
 * @new: the new string
 * @str: old string.
 * @env: env
 * @e: exit status.
 * Return: no return value.
 */

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

/**
 * change_value - change the string to it's new value.
 * @str: the string.
 * @env: env
 * @e: exit status.
 * Return: the new value of str.
 */

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

/**
 * expand - expand.
 * @str: string to expand.
 * @env: env
 * @e: exit status.
 * Return: the new string.
 */

t_string *expand(t_string *str, t_env *env, int e)
{
	return (change_value(str, env, e));
}
