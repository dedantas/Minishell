/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:45:34 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/12 18:46:01 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(t_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value); // FIXED: Duplicate the string
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;
	
	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	skip_whitespace(char **line)
{
	while (**line && ft_isspace(**line))
		(*line)++;
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
** Lê conteúdo entre aspas (com suporte a aspas escapadas)
*/
char *read_single_quote(char **line)
{
	char *start = *line + 1; // pula o '
	char *end = start;

	while (*end && *end != '\'')
		end++;

	*line = (*end == '\'') ? end + 1 : end; // avança a linha
	return (ft_substr(start, 0, end - start));
}

char *read_double_quote(char **line)
{
	char	*start = *line + 1; // pula o "
	char *end = start;

	while (*end && *end != '"')
		end++;
	*line = (*end == '"') ? end + 1 : end; // avança a linha
	return (ft_substr(start, 0, end - start)); // $ ainda será expandido depois
}

char *read_word(char **line)
{
	char	*start;

	start = *line;
	while (**line && !ft_isspace(**line) && !is_operator(**line))
		(*line)++;
	return (ft_substr(start, 0, *line - start));
}

/*
** Lexer principal com melhor tratamento de erros
*/
t_token *lexer(char *line)
{
	t_token	*tokens = NULL;
	char	*value;

	while (*line)
	{
		skip_whitespace(&line);
		if (!*line)
			break;
		if (*line == '\'')
		{
			value = read_single_quote(&line);
			add_token(&tokens, new_token(WORD, value));
			free(value);
		}
		else if (*line == '"')
		{
			value = read_double_quote(&line);
			add_token(&tokens, new_token(WORD, value));
			free(value);
		}
		else if (*line == '|')
		{
			add_token(&tokens, new_token(PIPE, "|"));
			line++;
		}
		else if (*line == '<' && *(line + 1) == '<')
		{
			add_token(&tokens, new_token(HEREDOC, "<<"));
			line += 2;
		}
		else if (*line == '>' && *(line + 1) == '>')
		{
			add_token(&tokens, new_token(APPEND, ">>"));
			line += 2;
		}
		else if (*line == '<')
		{
			add_token(&tokens, new_token(IN, "<"));
			line++;
		}
		else if (*line == '>')
		{
			add_token(&tokens, new_token(OUT, ">"));
			line++;
		}
		else
		{
			value = read_word(&line);
			add_token(&tokens, new_token(WORD, value));
			free(value);
		}
	}
	return tokens;
}
