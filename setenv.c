#include "exec.h"

/**
 * _setenv - function to add env variable to env
 * @cmd: variable to add to env
 * @genv: env passed as parameter
 * @status: third parameter
 *Return: 0 on success otherwise 1
*/

int _setenv(char **cmd, t_env **genv, int status)
{
	(void) status;
	if (!cmd[1] || !cmd[2] || cmd[3])
	{
		write(2, "Number Of Argument Not Valid\n", 29);
		return (1);
	}
	if (!find_env_p(cmd[1], *genv))
		newnode(cmd[1], cmd[2], genv);
	else
		replace_env(cmd[1], cmd[2], *genv);
	return (0);
}
