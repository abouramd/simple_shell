#include "exec.h"

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
	while(paths[i])
	{
		comand = malloc(strlen(paths[i]) + strlen(cmd) + 3);
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

int exec_cmd(char **cmd, t_env *genv)
{
	int ret = 0, flag = 0;
	pid_t id;
	int status;
	char *comand;
	if (cmd[0][0] != '/' && cmd[0][0] != '.')
	{
		flag = 1;
		comand = get_path(cmd[0], genv);
	}
	if (!comand || access(comand, F_OK) == -1)
	{
		if (errno == EACCES)
			ret = 126;
		else
			ret = 127;
		perror(NULL);
	}
	else
	{
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
			char **env = list_to_env(genv);
			execve(comand, cmd, env);
			if (errno == EACCES)
				ret = 126;
			 free_matrix(env);
			 exit(ret);
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