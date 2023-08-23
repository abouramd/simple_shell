#include "exec.h"

/**
 * numdigit - function to check if exit argument valid
 * @num: first parameter
 * Return: Success
 */
int numdigit(char *num)
{
	int i;

	i = 0;
	if (num[i] && (num[i] == '-' || num[i] == '+'))
		i++;
	while (num[i] && num[i] >= '0' && num[i] <= '9')
	{
		i++;
	}
	return (-1);
}

/**
 * ft_exit - builtin function to exit the programe with error number
 * @cmd: first argument
 * @genv: second argumnet
 * Return: the number hold by cmd[1]
*/
int ft_exit(char **cmd, t_env **genv)
{
	(void)genv;

	if (!cmd[1])
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	else if (numdigit(cmd[1]) >= 0)
	{
		write(1, "exit\n", 5);
		exit(ft_atoi(cmd[1]));
	}
	else
	{
		write(2, "exit\n", 5);
		write(2, cmd[1], strlen(cmd[1]));
		write(2, ": numeric argument required\n", 28);
	}
	exit(255);
}
