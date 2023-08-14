#include "pars.h"
#include "shell.h"

void new_env(t_env **head, char *value, char *key)
{
	t_env *node;
	static t_env *s;

	node = malloc(sizeof(t_env));
	if (!node)
		return;
	node->key = strdup(key);
	if (value)
		node->value = strdup(value);
	else
	 	node->value = NULL;
	node->next = NULL;
	if (!*head)
	{
		*head = node;
		s = node;
	}
	else if (s)
	{
		s->next = node;
		s = node;
	}
}


void free_env(t_env **env)
{
	if (env && *env)
	{
		free_env(&(*env)->next);
		free((*env)->key);
		free((*env)->value);
		free(*env);
	}
}
t_env *fill_env(char **env)
{
	t_env *nenv = NULL;
	char *key;
	char *value;
	char *str;
	size_t index = 0;

	while (env[index])
	{
		value = NULL;
		str = strchr(env[index], '=');
		if (str)
		{
			value = str + 1;
			*str = 0;
		}
		key = env[index];
		new_env(&nenv, value, key);
		index++;
	}
	return (nenv);
}

