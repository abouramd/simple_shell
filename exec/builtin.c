#include "exec.h"

int builtin(char **cmd, t_env **genv)
{
	t_built builtin[] = {
		{"exit", ft_exit},
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"alias", _alias},
		{"cd", _cd},
		{NULL, NULL},
	};
	int i;
	for (i = 0; builtin[i].builtin; i++)
	{
		if (!strcmp(builtin[i].builtin, cmd[0]))
		{
			return(builtin[i].func(cmd, genv));
		}
	}
	return (0);
}