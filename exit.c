#include "exec.h"

/**
 * numdigit - function to check if exit argument valid
 * @num: first parameter
 * Return: Success
 */
int numdigit(char *num)
{
	int i;
	int flg = 0;

	i = 0;
	if (num[i] && (num[i] == '-' || num[i] == '+'))
		i++;
	while (num[i] && num[i] >= '0' && num[i] <= '9')
	{
		i++;
		flg = 1;
	}
	if (flg)
		return (0);
	return (1);
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

	free_env(genv);
	if (!cmd[1])
	{
		my_free();
		exit(0);
	}
	else if (numdigit(cmd[1]) == 0)
	{
		int e;

		e = ft_atoi(cmd[1]);
		my_free();
		exit(e);
	}
	else
	{
		write(2, cmd[1], strlen(cmd[1]));
		write(2, ": numeric argument required\n", 28);
	}
	my_free();
	exit(255);
}
