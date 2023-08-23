#include "exec.h"
/**
 * update_pwd - function to update pwd in env
 * @genv: env passed as parametre
 * Return: void
 */
void update_pwd(t_env ***genv)
{
	char cwd[PATH_MAX];
	t_env *head = *(*genv);

	getcwd(cwd, PATH_MAX);
	while (head->next)
	{
		if (strcmp(head->key, "HOME") == 0)
		{
			free(head->value);
			head->value = malloc(strlen(cwd) + 1);
			strcpy(head->value, cwd);
			return;
		}
		head = head->next;
	}
	return;

}

/**
 * update_oldpwd - fucntion to update OLDPWD in env
 * @v: directory to set in OLDPWD
 * @genv: env passed as parameter
 * Return: void
 */

void update_oldpwd(char *v, t_env **genv)
{
	t_env *head = (*genv);

	while (head->next)
	{
		if (strcmp(head->key, "OLDPWD") == 0)
		{
			free(head->value);
			head->value = malloc(strlen(v) + 1);
			strcpy(head->value, v);
			return;
		}
		head = head->next;
	}
}

/**
 * _cd - builtin function to change current directory
 * @cmd: command line with option passed as parameter
 *  @genv: env passed as parameter
 *  Return: 0 on success otherwise error number
 */

int _cd(char **cmd, t_env **genv)
{
	char buf[PATH_MAX];
	int ret = 1;

	getcwd(buf, PATH_MAX);
	if (!cmd[1])
	{
		ret = chdir(find_env("HOME"));
		update_pwd(&genv);
		return (ret);
	}
	else if (cmd[1] && cmd[2])
	{
		perror("cd: too many argument");
		return (ret);
	}
	else if (cmd[1] && strcmp(cmd[1], "-") != 0)
	{
		ret = chdir(cmd[1]);
		update_oldpwd(buf, genv);
		return (ret);
	}
	else
	{
		ret = chdir(find_env("OLDPWD"));
		update_oldpwd(buf, genv);
		return (ret);
	}

}