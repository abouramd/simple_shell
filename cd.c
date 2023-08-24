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
		if (strcmp(head->key, "PWD") == 0)
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
 * chnge_dir - function to change directory
 * @str: first parameter
 * @cwd: second parameter
 * @genv: third parameter
 * Return: error Number
 */

int chnge_dir(char *str, char *cwd, t_env **genv)
{
	int ret = 0;

	ret = chdir(str);
	if (ret != 0)
		return (erro(str, 1));
	update_oldpwd(cwd, genv);
	update_pwd(&genv);
	return (ret);
}

/**
 * _cd - builtin function to change current directory
 * @cmd: command line with option passed as parameter
 * @genv: env passed as parameter
 * @status: third parameter
 *  Return: 0 on success otherwise error number
 */

int _cd(char **cmd, t_env **genv, int status)
{
	char *p, buf[PATH_MAX];
	int ret = 1;

	(void) status;
	getcwd(buf, PATH_MAX);
	if (!cmd[1])
	{
		p = find_env_p("HOME", *genv);
		if (!p)
			return (0);
		ret = chdir(p);
		update_pwd(&genv);
		update_oldpwd(buf, genv);
		return (ret);
	}
	else if (cmd[1] && cmd[2])
		return (erro(NULL, 2));
	else if (cmd[1] && strcmp(cmd[1], "-") != 0)
		return (chnge_dir(cmd[1], buf, genv));
	p = find_env_p("OLDPWD", *genv);
	if (!p)
	{
		p = getcwd(NULL, 0);
		puts(p);
		free(p);
		return (0);
	}
	ret = chdir(p);
	if (ret != 0)
		return (erro(p, 1));
	printf("%s\n", find_env("OLDPWD"));
	update_oldpwd(buf, genv);
	update_pwd(&genv);
	return (ret);
}
