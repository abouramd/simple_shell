#include "exec.h"

void newnode(char *k, char *v, t_env **genv)
{
	t_env *head = *genv;
	t_env *node = malloc(sizeof(t_env));
	node->key = malloc(strlen(k) + 1);
	node->value = malloc(strlen(v) + 1);
	node->next = NULL;
	while(head->next)
	{
		head = head->next;
	}
	head->next = node;
}

void delete_node(char *k, t_env **genv)
{
	t_env *current;
	t_env *prev;
	current = *genv;
	prev = current;
	if (!(*genv))
		return ;
	else if (strcmp((*genv)->key, k) == 0)
	{
		(*genv) = (*genv)->next;
		free(current);
		return ;
	}
	while(genv)
	{
		if (strcmp(current->key, k) == 0)
		{
			prev = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	current = prev;
	return ;
}

char **list_to_env(t_env *genv)
{
	char **env = NULL;
	t_env *head = genv;
	int i = 0;
	while(head)
	{
		i++;
		head = head->next;
	}
	head = genv;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(head)
	{
		env[i] = malloc(strlen(head->key) + strlen(head->value) + 3);
		strcpy(env[i], head->key);
		strcat(env[i], "=");
		strcat(env[i], head->value);
		head = head->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

char **free_matrix(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}