#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_env {
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

struct s_env *genv;

char *find_env(char *s);

#endif
