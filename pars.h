#ifndef PARS_H
#define PARS_H

#include "shell.h"

typedef enum s_type {
	STR,
	PIP,
	SMC,
} t_type;

typedef struct s_string {
	char c;
	struct s_string *next;
} t_string;

/**
 * struct s_getline - getline member
 * @characters: number of characters in the string
 * @buffer: the buffer to fill
 * @bufsize: the size of the buffer
 */

typedef struct s_getline {
	size_t	characters;
	char	*buffer;
	size_t	bufsize;
} t_getline;

/**
 * struct s_lexer - split the member
 * @content: the content
 * @type: the type of the token
 */

typedef struct s_lexer {
	t_type type;
	t_string *content;
	struct s_lexer *next;
} t_lexer;

t_lexer *lexer(t_getline* line);

char **fill_cmd(t_lexer **lexer, bool *pip, bool *smc);

#endif
