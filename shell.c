#include "shell.h"
#include "pars.h"
#include <stdio.h>
#include <unistd.h>

void string_print(t_string *ptr)
{
	if (!ptr)
		return;
	write(1, &ptr->c, 2);
	string_print(ptr->next);
}

void lexer_print(t_lexer *ptr)
{
	char str[3][100] = {"Type : STR\n", "Type : PIP\n", "Type : SMC\n"};
	if (!ptr)
		return;
	write(1, "Node : ", 7);
	string_print(ptr->content);
	write(1, "  ", 2);
	write(1, str[ptr->type], 11);
	lexer_print(ptr->next);

}

void cmd_print(t_lexer *ptr)
{
	char **cmd;
	bool pip;
	bool smc;

	while (ptr)
	{
		printf("----------------------\n");
		cmd = fill_cmd(&ptr, &pip, &smc);
		printf("pip = %s\n", pip?"true":"false");
		printf("smc = %s\n", smc?"true":"false");
		while (cmd && *cmd)
			printf("cmd = %s\n", *(cmd++));
		if (!cmd)
			printf("cmd = %s\n", *cmd);
		printf("----------------------\n");
	}
}


void env_print(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}


int main(int ac, char **av, char **env)
{
	t_getline l;
	t_lexer *x;

	genv = fill_env(env);
	//env_print(genv);
	while (true) {
		write(1, "prompt >> ", 10);
		l.characters = getline(&l.buffer,&l.bufsize,stdin);
		if (l.characters == -1)
			return (0);
		x = lexer(&l);
		// lexer_print(x);
		cmd_print(x);
	}

	return (0);
}

