#include "exec.h"

/**
 * is_builtin - function to check if command is builtin
 * @cmd: command to check
 * Return: 1 on Success otherwise 0
 */

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!strcmp(cmd, "exit") || !strcmp(cmd, "setenv") || !strcmp(cmd, "env")
		|| !strcmp(cmd, "unsetenv") || !strcmp(cmd, "alias") || !strcmp(cmd, "cd"))
		return (1);
	return (0);
}

/**
 * exec - base function to run builtin and regulare command
 * @ptr: first argument
 * @genv: second argumnet
 * @status: third argumnet
 * Return: 0 on sucess otherwise error number
 */

void exec(t_lexer *ptr, t_env **genv, int *status)
{
	char **cmd;
	bool pip;
	bool sim;

	while (ptr)
	{
		cmd = fill_cmd(&ptr, &pip, &sim, *status, *genv);
		if (is_builtin(cmd[0]))
		{
			*status = builtin(cmd, genv, *status);
		}
		else
			*status = exec_cmd(cmd, *genv);
	}
}
