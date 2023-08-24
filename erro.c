#include "exec.h"

/**
 * erro - function to print error message
 * @str: first parameter
 * @flag: second parameter
 * Return: error number
 */

int erro(char *str, int flag)
{
	if (flag == 1)
	{
		write(2, "./hsh: 1: cd: can't cd to ", 26);
		write(2, str, strlen(str));
		write(2, "\n", 1);
		return (1);
	}
	else if (flag == 2)
	{
		perror("cd: too many argument");
		return (1);
	}
	return (0);
}