#include "pars.h"

/**
 * string_size - count string size.
 * @ptr: the string.
 * Return: size of the string.
 */

size_t string_size(t_string *ptr)
{
	if (!ptr)
		return (0);
	return (string_size(ptr->next) + 1);
}

/**
 * convert_string - t_string to char *.
 * @s: t_string data.
 * Return: char * content the string data.
 */

char *convert_string(t_string *s)
{
	char *str;
	size_t size;
	size_t index = 0;
	char qout = 0;

	size = string_size(s);
	str = my_malloc(sizeof(char) * (size + 1));
	if (!str)
		return (str);
	while (s)
	{
		if (!qout && (s->c == '"' || s->c == '\''))
			qout = s->c;
		else if (qout == s->c)
			qout = 0;
		else
			str[index++] = s->c;
		s = s->next;
	}
	str[index] = 0;
	return (str);
}

/**
 * cmd_size - count cmd size.
 * @lexer: the leaxer.
 * Return: size of lexer.
 */

size_t cmd_size(t_lexer *lexer)
{
	size_t count = 0;

	while (lexer && lexer->type == STR)
	{
		lexer = lexer->next;
		count++;
	}
	return (count);
}

/**
 * split_lexer - fill the lexer from command.
 * @head: head of lexer.
 * @str: the string in the lexer.
 * Return: void.
 */

void split_lexer(t_lexer **head, t_string *str)
{
	char qout = 0;
	t_string *save;

	while (str)
	{
		save = NULL;
		while (str && (str->c == ' ' || str->c == '\t' || str->c == '\n'))
			str = str->next;
		while (str)
		{
			if (!qout && (str->c == '"' || str->c == '\''))
				qout = str->c;
			else if (qout == str->c)
				qout = 0;
			if (qout == 0)
				if (str->c == ' '
				|| str->c == '\t'
				|| str->c == '\n')
					break;
			new_string(&save, str->c);
			str = str->next;
		}
		if (save)
			new_lexer(head, save, STR);
	}
}

/**
 * new_cmd - creat a new cmd.
 * @lexer: my lexer.
 * @pip: if pipe after cmd.
 * @smc: if smc after cmd.
 * Return: lexer of new_cmd.
 */

t_lexer *new_cmd(t_lexer **lexer, bool *pip, bool *smc)
{
	t_lexer *head = NULL;
	t_string *str;

	*smc = false;
	*pip = false;
	while (*lexer && (*lexer)->type == STR)
	{
		str = expand((*lexer)->content);
		/* cmd[index++] = convert_string((*lexer)->content); */
		split_lexer(&head, str);
		*lexer = (*lexer)->next;
	}
	if (!*lexer || (*lexer)->type == SMC)
		*smc = true;
	else
		*pip = true;
	if (*lexer)
		*lexer = (*lexer)->next;
	return (head);
}

/**
 * fill_cmd - fill cmd in 2d arr.
 * @lexer: my lexer.
 * @pip: if pipe after cmd.
 * @smc: if smc after cmd.
 * Return: 2d arr to the cmd.
 */

char **fill_cmd(t_lexer **lexer, bool *pip, bool *smc)
{
	char **cmd;
	t_lexer *head = NULL;
	size_t size;
	size_t index = 0;

	head = new_cmd(lexer, pip, smc);
	size = cmd_size(head);
	cmd = my_malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	while (head)
	{
		cmd[index++] = convert_string((head)->content);
		head = (head)->next;
	}
	return (cmd);
}


