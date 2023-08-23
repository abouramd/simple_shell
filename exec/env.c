#include "exec.h"

int _env(char **cmd, t_env **genv)
{
	(void)cmd;
	t_env *head = (*genv);
	if (!head)
		return (-2);
	while(head)
	{
		write(1, head->key, strlen(head->key));
		write(1, "=", 1);
		write(1, head->value, strlen(head->value));
		write(1, "\n", 1);
		head = head->next;
	}
	return (0);
}