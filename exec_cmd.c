#include "exec.h"

/**
 *get_path - function to get executable path from env
 *@cmd: command to find ther path
 *@genv: env to find path for exeutable
 * Return: return executable path if found otherwise NULL
 */

char *get_path(char *cmd, t_env *genv)
{
	int i;
	struct stat s;
	char **paths;
	char *comand;
	char *path;

	(void)genv;
	path = find_env("PATH");
	if (!path || !(*path))
		return (NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths && paths[i])
	{
		comand = my_malloc(strlen(paths[i]) + strlen(cmd) + 3);
		strcpy(comand, paths[i]);
		strcat(comand, "/");
		strcat(comand, cmd);
		if (stat(comand, &s) == 0)
		{
			free_matrix(paths);
			return (comand);
		}
		i++;
	}
	free_matrix(paths);
	return (NULL);
}

/**
 * exec_erro - function to print exec function error
 * @cmd: first parameter
 * @comand: second parameter
 * @i: fourth parameter
 * Return: error number
 */
int exec_erro(char **cmd, char *comand, int i)
{
	int ret = 0;

	if (i == 1)
	{
		if (!comand)
		{
			write(2, "./hsh: 1: ", 10);
			if (cmd && cmd[0])
				write(2, cmd[0], strlen(cmd[0]));
			write(2, ": not found\n", 12);
		}
	}
	else if (i == 2)
	{
		if (errno == EACCES)
			ret = 126;
		else
			ret = 127;
		if (comand)
			perror(NULL);
	}
	return (ret);
}

/**
 * exec_cmd -  function to execute regulare command
*@cmd: command to execute with opetion
*@genv: env passed as parameter
*Return: 0 on Success otherwise error number
*/

int exec_cmd(char **cmd, t_env *genv)
{
	int ret = 0, flag = 0, status = 0;
	pid_t id;
	char *comand = cmd[0];

	if (comand && !strchr(comand, '/') && comand[0] != '.')
	{
		flag = 1;
		comand = get_path(cmd[0], genv);
		exec_erro(cmd, comand, 1);
	}
	if (!comand || access(comand, F_OK) == -1)
		ret = exec_erro(cmd, comand, 2);
	else
	{
		id = fork();
		if (id == -1)
		{
			if (flag)
				free(comand);
			perror("fork fail");
			return (1);
		}
		if (id == 0)
		{
			execve(comand, cmd, list_to_env(genv));
			perror(NULL);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	return (ret);
}
