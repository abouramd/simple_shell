#include "exec.h"

/**
 * _setenv - function to add env variable to env
 * @cmd: variable to add to env
 * @genv: env passed as parameter
 *Return: 0 on success otherwise 1
*/

int _setenv(char **cmd, t_env **genv)
{
	if (!cmd[1] || !cmd[2])
	{
		perror("Number Of Argument Not Valid");
		return (1);
	}
	newnode(cmd[1], cmd[2], genv);
	return (0);
}
