#ifndef EXEC_H
#define EXEC_H

#include "../pars.h"
#include "../shell.h"
#include <linux/limits.h>
#include <sys/stat.h>
#include <errno.h>
#include <bsd/string.h>


typedef struct builtin_struct
{
	char *builtin;
	int (*func)(char **cmd, t_env **genv);
}t_built;

	
void exec(t_lexer *ptr, t_env *genv);
int is_builtin(char *cmd);

	
void newnode(char *k, char *v, t_env **genv);
void delete_node(char *k, t_env **genv);
char **list_to_env(t_env *genv);
char **free_matrix(char **str);

	
void update_pwd(t_env ***genv);
void update_oldpwd(char *v, t_env **genv);
int _cd(char **cmd, t_env **genv);


int _env(char **cmd, t_env **genv);

	
int builtin(char **cmd, t_env **genv);

	
int _setenv(char **cmd, t_env **genv);

	
int _unsetenv(char **cmd, t_env **genv);

	
char	**ft_split(char *s, char c);

	
int exec_cmd(char **cmd, t_env *genv);
char *get_path(char *cmd, t_env *genv);


int ft_exit(char **cmd, t_env **genv);

int _alias(char **cmd, t_env **genv);

#endif