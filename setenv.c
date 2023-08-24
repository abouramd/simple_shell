#include "exec.h"

/**
 * _setenv - function to add env variable to env
 * @cmd: variable to add to env
 * @genv: env passed as parameter
 *Return: 0 on success otherwise 1
*/

int _setenv(char **cmd, t_env **genv, int status)
{
	(void) status;
	if (!cmd[1] || !cmd[2])
	{
		perror("Number Of Argument Not Valid");
		return (1);
	}
	if (!find_env_p(cmd[1], *genv))
		newnode(cmd[1], cmd[2], genv);
	return (0);
}
