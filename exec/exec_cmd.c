#include "exec.h"

char *get_path(char *cmd, t_env *genv)
{
	struct stat s;
	char *path = find_env("PATH");
	char **paths;
	char *comand;
	if (!path || !(*path))
		return (NULL);
	// printf("\n%s\n", path);
	paths = ft_split(path, ':');
	int i = 0;
	// while(paths[i])
	// {
	// 	printf("\n%s\n", paths[i]);
	// 	i++;
	// }
	while(paths[i])
	{
		comand = malloc(strlen(paths[i]) + strlen(cmd) + 3);
		strcpy(comand, paths[i]);
		strcat(comand, "/");
		strcat(comand, cmd);
		// printf("\n\n==>%s\n\n", comand);
		if (stat(comand, &s) == 0)
		{
			// free paths
			return (comand);
		}
		i++;
	}
	// free paths
	return (NULL);
}

int exec_cmd(char **cmd, t_env *genv)
{
	int ret = 0, flag = 0;
	pid_t id;
	int status;
	char *comand;
	// printf("4444444\n");
	if (cmd[0][0] != '/' && cmd[0][0] != '.')
	{
		flag = 1;
		// printf("fdfdf\n");
		comand = get_path(cmd[0], genv);
		// printf("3333\n");
	}
	if (!comand || access(comand, F_OK) == -1)
	{
		// if (!comand)
			// printf("ddasdasasfa\n");
		// printf("11111\n");
		if (errno == EACCES)
			ret = 126;
		else
			ret = 127;
		perror(NULL);
	}
	else
	{
		// printf("000000\n");
		id = fork();
		if (id == -1)
		{
			if (flag)
				free(comand);
			perror("fork fail");
			return 1;
		}
		if (id == 0)
		{
			// printf("555555\n");
			// printf("\n%s\n", comand);
			char **env = list_to_env(genv);
			execve(comand, cmd, env);
			if (errno == EACCES)
				ret = 126;
			// free env fro list_to_env
			// ft_exit(ret);
			// exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(comand);
	return (ret);
}