#include "exec.h"

int _setenv(char **cmd, t_env **genv)
{
	if (!cmd[1] || !cmd[2])
	{
		perror("Number Of Argument Not Valid");
		return -1;
	}
	newnode(cmd[1], cmd[2], genv);
	return 0;
}