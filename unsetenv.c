#include "exec.h"

/**
 * _unsetenv - function to unset variable from env
 * @cmd: variable to unset
 * @genv: env passed as parameter
 * Return: 0 on Success otherwise 1
 */

int _unsetenv(char **cmd, t_env **genv)
{
	if (!cmd[1])
	{
		perror("Number Of Argument Not Valid");
		return (1);
	}
	delete_node(cmd[1], genv);
	return (0);
}
