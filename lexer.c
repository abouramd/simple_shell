#include "pars.h"

void new_string(t_string **head, char c)
{
	t_string *str;
	static t_string *s;

	str = calloc(sizeof(t_string), 1);
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

void new_lexer(t_lexer **head, t_string *c, t_type type)
{
	t_lexer *node;
	static t_lexer *s;

	node = calloc(sizeof(t_lexer), 1);
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

t_lexer *lexer(t_getline *line)
{
	t_lexer *head = NULL;
	t_string	*str;
	size_t i = 0;
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
			if (!qout && (line->buffer[i] == '"' || line->buffer[i] == '\''))
				qout = line->buffer[i];
			else if (qout == line->buffer[i])
				qout = 0;
			if (qout == 0)
				if (line->buffer[i] == ' '
				|| line->buffer[i] == '\t'
				|| line->buffer[i] == '\n'
				|| line->buffer[i] == '|'
				|| line->buffer[i] == ';')
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
