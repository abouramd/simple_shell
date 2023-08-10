#include "shell.h"
#include "pars.h"
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

int main()
{
	t_getline l;
	t_lexer *x;

	while (true) {
		write(1, "prompt >> ", 10);
		l.characters = getline(&l.buffer,&l.bufsize,stdin);
		if (l.characters == -1)
			return (0);
		printf("-> %ld %s", l.characters, l.buffer);
		x = lexer(&l);
		lexer_print(x);
	}

	return (0);
}

