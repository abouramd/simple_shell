#include "exec.h"

/**
 * ft_exit - builtin function to exit the programe with error number
 * @cmd: first argument
 * @genv: second argumnet
 * Return: the number hold by cmd[1]
*/

int ft_exit(char **cmd, t_env **genv)
{
	(void)cmd;
	(void)genv;

	return (0);
}
