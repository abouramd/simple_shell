#include "shell.h"
#include "my_alloc.h"
#include "pars.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

t_env *genv;
void exec(t_lexer *ptr, t_env *genv);

/**
 * find_env - find th value of a key.
 * @s: the key.
 * Return: the value of var.
 */

char *find_env(char *s)
{
	t_env *tmp;

	tmp = genv;
	while (tmp)
	{
		if (!strcmp(tmp->key, s))
			return (tmp->value);
		tmp = tmp->next;
	}
	return NULL;
}

void string_print(t_string *ptr)
{
	if (!ptr)
		return;
	write(1, &ptr->c, 1);
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
	/* env_print(genv); */
	(void) ac;
	(void) av;
	while (true) {
		l.bufsize = 0;
		l.buffer = NULL;
		write(1, "prompt >> ", 10);
		l.characters = getline(&l.buffer,&l.bufsize,stdin);
		if (l.characters == -1)
			return (free_env(&genv), free(l.buffer), 0); /* replace 0 with the exit status*/
		x = lexer(&l);
		exec(x, genv);
		// printf("key  = %s\n", genv->key);
		// printf("value  = %s\n", genv->value);
		/* lexer_print(x); */
		// cmd_print(x);
		my_free(); /* free all the data that you allocat with my_alloc */
		free(l.buffer); /* free buffer */
	}
	return (0);
}

