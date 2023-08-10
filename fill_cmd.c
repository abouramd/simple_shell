#include "pars.h"

size_t string_size(t_string *ptr)
{
	if (!ptr)
		return (0);
	return (string_size(ptr->next) + 1);
}

char *convert_string(t_string *s)
{
	char *str;
	size_t size;
	size_t index = 0;

	size = string_size(s);
	str = calloc(sizeof(char), size + 1);
	if (!str)
		return (str);
	while (s)
	{
		str[index++] = s->c;
		s = s->next;
	}
	return (str);
}

size_t cmd_size(t_lexer *lexer, bool *pip, bool *smc)
{
	size_t count = 0;

	*smc = false;
	*pip = false;
	while (lexer && lexer->type == STR)
	{
		lexer = lexer->next;
		count++;
	}
	if (!lexer || lexer->type == SMC)
		*smc = true;
	else
		*pip = true;
	return (count);
}

char **fill_cmd(t_lexer **lexer, bool *pip, bool *smc)
{
	char **cmd;
	size_t size;
	size_t index = 0;

	size = cmd_size(*lexer, pip, smc);
	cmd = calloc(sizeof(char *), size + 1);
	if (!cmd)
		return (NULL);
	while (*lexer && (*lexer)->type == STR)
	{
		cmd[index++] = convert_string((*lexer)->content);
		*lexer = (*lexer)->next;
	}
	if (*lexer)
		*lexer = (*lexer)->next;
	return (cmd);
}
