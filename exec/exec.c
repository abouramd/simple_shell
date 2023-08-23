#include "exec.h"

int is_builtin(char *cmd)
{
	if (!strcmp(cmd, "exit") || !strcmp(cmd, "setenv") || !strcmp(cmd, "env") 
		|| !strcmp(cmd, "unsetenv") || !strcmp(cmd, "alias") || !strcmp(cmd, "cd"))
		return (1);
	return (0);
}

void exec(t_lexer *ptr, t_env *genv)
{
	char **cmd;
	bool pip;
	bool sim;
	int ret;
	cmd = fill_cmd(&ptr, &pip, &sim);
	
	if (is_builtin(cmd[0]))
	{
		// printf("\n\n11111111\n\n");
		ret = builtin(cmd, &genv);
	}
	else
		ret = exec_cmd(cmd, genv);

}