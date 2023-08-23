#include "exec.h"

int _unsetenv(char **cmd, t_env **genv)
{
	if (!cmd[1])
	{
		perror("Number Of Argument Not Valid");
		return -1;
	}
	delete_node(cmd[1], genv);
	return 0;
}