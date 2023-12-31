#ifndef PARS_H
#define PARS_H

#include "shell.h"

/**
 * enum s_type - type of token.
 * @STR: string type.
 * @PIP: | type.
 * @SMC: ; type.
 */

typedef enum s_type
{
	STR,
	PIP,
	SMC
} t_type;

/**
 * struct s_string - data type use in pars.
 * @c: the content of the node.
 * @next: thr next char.
 */

typedef struct s_string
{
	char c;
	struct s_string *next;
} t_string;

/**
 * struct s_getline - getline member
 * @characters: number of characters in the string
 * @buffer: the buffer to fill
 * @bufsize: the size of the buffer
 */

typedef struct s_getline
{
	ssize_t	characters;
	char	*buffer;
	size_t	bufsize;
} t_getline;

/**
 * struct s_lexer - split the member
 * @content: the content
 * @type: the type of the token
 * @next: next node.
 */

typedef struct s_lexer
{
	t_type type;
	t_string *content;
	struct s_lexer *next;
} t_lexer;


t_lexer *lexer(t_getline *line);

char **fill_cmd(t_lexer **lexer, bool *pip, bool *smc, int e, t_env *env);

void new_string(t_string **head, char c);

t_string *expand(t_string *str, t_env *env, int e);

t_env *fill_env(char **env);

char *convert_string(t_string *s);

void new_lexer(t_lexer **head, t_string *c, t_type type);

char *itoa(long num);

void free_env(t_env **env);

#endif
