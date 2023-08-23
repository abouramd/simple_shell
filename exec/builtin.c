#include "exec.h"

int builtin(char **cmd, t_env **genv)
{
	t_built builtin[] = {
		// {"exit", ft_exit(cmd, genv)},
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		// {"alias", _alias(cmd, genv)},
		{"cd", _cd},
		{NULL, NULL},
	};

	for (int i = 0; builtin[i].builtin; i++)
	{
		if (!strcmp(builtin[i].builtin, cmd[0]))
		{
			// printf("\n\n22222\n\n");
			return(builtin[i].func(cmd, genv));
		}
	}
}