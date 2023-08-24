#include "exec.h"

/**
 * _env - builtin function to print env
 * @cmd: first argument
 * @genv: env passed as parameter
 * Return: 0 on Success otherwise error number
 */
int _env(char **cmd, t_env **genv, int status)
{
	t_env *head = (*genv);
	(void) status;
	(void)cmd;
	if (!head)
		return (-2);
	while (head)
	{
		if (head->value)
		{
			write(1, head->key, strlen(head->key));
			write(1, "=", 1);
			write(1, head->value, strlen(head->value));
			write(1, "\n", 1);
		}
		head = head->next;
	}
	return (0);
}

