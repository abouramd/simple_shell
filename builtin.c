#include "exec.h"

/**
 * builtin - function to call apropriate builtin function
 *@cmd: first argument
 *@genv:  second argument
 * @status: third argumnet
 * Return: return 0 on success otherwise return error
 */
int builtin(char **cmd, t_env **genv, int status)
{
	t_built builtin[] = {
		{"exit", ft_exit},
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{NULL, NULL},
	};
	int i;

	for (i = 0; builtin[i].builtin; i++)
	{
		if (!strcmp(builtin[i].builtin, cmd[0]))
		{
			return (builtin[i].func(cmd, genv, status));
		}
	}
	return (0);
}
