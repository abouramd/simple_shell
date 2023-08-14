#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "my_alloc.h"


typedef struct s_env {
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

char *find_env(char *s);

#endif
