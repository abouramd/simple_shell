#ifndef EXEC_H
#define EXEC_H

#include "pars.h"
#include "shell.h"
#include <linux/limits.h>
#include <sys/stat.h>
#include <errno.h>


/**
 * struct builtin_struct - struct to hold builtin function
 * @builtin: first argumnet
 * @func: second argumnet
 */

typedef struct builtin_struct
{
	char *builtin;
	int (*func)(char **cmd, t_env **genv, int status);
}	t_built;

void exec(t_lexer *ptr, t_env **genv, int *status);
int is_builtin(char *cmd);

int erro(char *str, int flag);

int	ft_atoi(const char *str);

void newnode(char *k, char *v, t_env **genv);
void replace_env(char *k, char *v, t_env *genv);
void delete_node(char *k, t_env **genv);
char **list_to_env(t_env *genv);
char **free_matrix(char **str);


void update_pwd(t_env ***genv);
void update_oldpwd(char *v, t_env **genv);
int _cd(char **cmd, t_env **genv, int status);


int _env(char **cmd, t_env **genv, int status);

int builtin(char **cmd, t_env **genv, int status);


int _setenv(char **cmd, t_env **genv, int status);

int _unsetenv(char **cmd, t_env **genv, int status);


char	**ft_split(char *s, char c);


int exec_cmd(char **cmd, t_env *genv);
char *get_path(char *cmd, t_env *genv);


int ft_exit(char **cmd, t_env **genv, int status);


#endif
