#include "pars.h"

/**
 * new_string - new node of string.
 * @head: the head of the linked list.
 * @c: the content of the node.
 * Return: no return value.
 */

void new_string(t_string **head, char c)
{
	t_string *str;
	static t_string *s;

	str = my_malloc(sizeof(t_string));
	if (!str)
		return;
	str->c = c;
	if (!*head)
	{
		*head = str;
		s = str;
	}
	else if (s)
	{
		s->next = str;
		s = str;
	}
}

/**
 * new_lexer - new node of lexer.
 * @head: the head of the linked list.
 * @c: the content of the node.
 * @type: the type of the content.
 * Return: no return value.
 */

void new_lexer(t_lexer **head, t_string *c, t_type type)
{
	t_lexer *node;
	static t_lexer *s;

	node = my_malloc(sizeof(t_lexer));
	if (!node)
		return;
	node->content = c;
	node->type = type;
	if (!*head)
	{
		*head = node;
		s = node;
	}
	else if (s)
	{
		s->next = node;
		s = node;
	}
}

/**
 * check_char - check for limeter.
 * @line: the command.
 * @i: the index now.
 * @qout: the qout.
 * Return: bool to stop or contunie.
 */

bool check_char(t_getline *line, int i, char *qout)
{
	if (!*qout && (line->buffer[i] == '"' || line->buffer[i] == '\''))
		*qout = line->buffer[i];
	else if (*qout == line->buffer[i])
		*qout = 0;
	if (*qout == 0)
		if (line->buffer[i] == ' '\
		|| line->buffer[i] == '\t'\
		|| line->buffer[i] == '\n'\
		|| line->buffer[i] == '|'\
		|| line->buffer[i] == ';')
			return (true);
	return (false);
}

/**
 * lexer - split and token the command.
 * @line: the command.
 * Return: linked list of lexer.
 */

t_lexer *lexer(t_getline *line)
{
	t_lexer *head = NULL;
	t_string	*str;
	ssize_t i = 0;
	char qout = 0;

	while (i < line->characters)
	{
		str = NULL;
		while (i < line->characters && (line->buffer[i] == ' '
			|| line->buffer[i] == '\t' || line->buffer[i] == '\n'))
			i++;
		if (i == line->characters)
			break;
		while (i < line->characters)
		{

			if (check_char(line, i, &qout))
				break;
			new_string(&str, line->buffer[i]);	
			i++;
		}
		if (str)
		{
			new_lexer(&head, str, STR);
			str = NULL;
		}
		if (line->buffer[i] == '|' || line->buffer[i] == ';')
		{
			new_string(&str, line->buffer[i]);
			if (line->buffer[i] == '|')
				new_lexer(&head, str, PIP);
			if (line->buffer[i] == ';')
				new_lexer(&head, str, SMC);
			i++;
		}
	}
	return (head);
}

