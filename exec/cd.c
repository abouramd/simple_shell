#include "exec.h"

void update_pwd(t_env ***genv)
{
	char cwd[PATH_MAX];
	getcwd(cwd, PATH_MAX);
	t_env *head = *(*genv);
	while(cwd && head->next)
	{
		if (strcmp(head->key, "HOME") == 0)
		{
			free(head->value);
			head->value = malloc(strlen(cwd) + 1);
			strcpy(head->value, cwd);
			return ;
		}
		head = head->next;
	}
	return ;

}

void update_oldpwd(char *v, t_env **genv)
{
	t_env *head = (*genv);
	while(head->next)
	{
		if (strcmp(head->key, "OLDPWD") == 0)
		{
			free(head->value);
			head->value = malloc(strlen(v) + 1);
			strcpy(head->value, v);
			return ;
		}
		head = head->next;
	}
}

int _cd(char **cmd, t_env **genv)
{
	char buf[PATH_MAX];
	getcwd(buf, PATH_MAX);
	int ret ;
	if (!cmd[1])
	{
		// printf("\nbefore pwd%s\n", find_env("PWD"));
		// printf("\nbefore oldpwd%s\n", find_env("OLDPWD"));
		ret = chdir(find_env("HOME"));
		update_pwd(&genv);
		// printf("\nafter pwd%s\n", find_env("PWD"));
		// printf("\nafter oldpwd%s\n", find_env("OLDPWD"));
		return (ret);
	}
	else if (cmd[1] && cmd[2])
	{
		perror("cd: too many argument");
		return 1;
	}
	else if (cmd[1] && strcmp(cmd[1], "-") != 0)
	{
		// printf("\nbefore pwd%s\n", find_env("PWD"));
		// printf("\nbefore oldpwd%s\n", find_env("OLDPWD"));
		ret = chdir(cmd[1]);
		update_oldpwd(buf, genv);
		// printf("\nafter pwd%s\n", find_env("PWD"));
		// printf("\nafter oldpwd%s\n", find_env("OLDPWD"));
		return ret;
	}
	else
	{
		// printf("\nbefore pwd%s\n", find_env("PWD"));
		// printf("\nbefore oldpwd%s\n", find_env("OLDPWD"));
		ret = chdir(find_env("OLDPWD"));
		update_oldpwd(buf, genv);
		// printf("\nafter pwd%s\n", find_env("PWD"));
		// printf("\nafter oldpwd%s\n", find_env("OLDPWD"));
		return ret;
	}

}