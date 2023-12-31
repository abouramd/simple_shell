#include "shell.h"
#include "my_alloc.h"
#include "pars.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

void siggnal(int signall);
void exec(t_lexer *ptr, t_env **genv, int *status);
t_env *genv;

/**
 * find_env_p - find in env.
 * @s: key.
 * @env: env.
 * Return: the value of key.
*/

char *find_env_p(char *s, t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!strcmp(tmp->key, s))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * find_env - find in env.
 * @s: key.
 * Return: the value of key.
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
	return (NULL);
}

/*
 * void string_print(t_string *ptr)
*{
*	if (!ptr)
*		return;
*	write(1, &ptr->c, 1);
*	string_print(ptr->next);
*}
*
*void lexer_print(t_lexer *ptr)
*{
*	char str[3][100] = {"Type : STR\n", "Type : PIP\n", "Type : SMC\n"};
*	if (!ptr)
*		return;
*	write(1, "Node : ", 7);
*	string_print(ptr->content);
*	write(1, "  ", 2);
*	write(1, str[ptr->type], 11);
*	lexer_print(ptr->next);
*
*}
*
*void cmd_print(t_lexer *ptr)
*{
*	char **cmd;
*	bool pip;
*	bool smc;
*
*	while (ptr)
*	{
*		printf("----------------------\n");
*		cmd = fill_cmd(&ptr, &pip, &smc, 0, NULL);
*		printf("pip = %s\n", pip?"true":"false");
*		printf("smc = %s\n", smc?"true":"false");
*		while (cmd && *cmd)
*			printf("cmd = %s\n", *(cmd++));
*		if (!cmd)
*			printf("cmd = %s\n", *cmd);
*		printf("----------------------\n");
*	}
*}
*
*
*void env_print(t_env *env)
*{
*	while (env)
*	{
*		printf("%s=%s\n", env->key, env->value);
*		env = env->next;
*	}
*}
*/

/**
 * main - start.
 * @ac: num of args.
 * @av: args.
 * @env: env.
 * Return: 0;
 */

int main(int ac, char **av, char **env)
{
	t_getline l;
	t_lexer *x;
	int status = 0;
	FILE *fptr = stdin;

	if (ac == 2)
		fptr = fopen(av[1], "r");
	if (!fptr)
	{
		write(2, "./hsh: 0: Can't open ", 21);
		write(2, av[1], strlen(av[1]));
		write(2, "\n", 1);
		return (127);
	}
	genv = fill_env(env);
	/* env_print(genv); */
	(void) ac;
	(void) av;
	while (true)
	{
		l.bufsize = 0;
		l.buffer = NULL;
		l.characters = getline(&l.buffer, &l.bufsize, fptr);
		if (l.characters == -1)
		{
			if (ac == 2)
				fclose(fptr);
			return (free_env(&genv), free(l.buffer), status);
		}
		x = lexer(&l);
		free(l.buffer); /* free buffer */
		exec(x, &genv, &status);
		/* lexer_print(x); */
		/* cmd_print(x);*/
		my_free(); /* free all the data that you allocat with my_alloc */
	}
	if (ac == 2)
		fclose(fptr);
	return (status);
}

