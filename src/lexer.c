/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:45:34 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/15 19:20:26 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Lê conteúdo entre aspas (com suporte a aspas escapadas)
*/
char	*read_quote(char **line, char quote)
{
	char	*start;
	char	*end;

	start = *line + 1;
	end = start;
	while (*end && *end != quote)
		end++;
	if (*end == quote)
		*line = end + 1;
	else
		*line = end;
	return (ft_substr(start, 0, end - start));
}

char	*read_word(char **line)
{
	char	*start;

	start = *line;
	while (**line && !ft_isspace(**line) && !is_operator(**line))
		(*line)++;
	return (ft_substr(start, 0, *line - start));
}

static int	handle_operators(t_token **tokens, char **line)
{
	if (**line == '|' )
		return (add_token(tokens, new_token(PIPE, "|", NO)), (*line)++, 1);
	if (**line == '<' && *(*line + 1) == '<')
		return (add_token(tokens, new_token(HEREDOC, "<<", NO)), *line += 2, 1);
	if (**line == '>' && *(*line + 1) == '>')
		return (add_token(tokens, new_token(APPEND, ">>", NO)), *line += 2, 1);
	if (**line == '<')
		return (add_token(tokens, new_token(IN, "<", NO)), (*line)++, 1);
	if (**line == '>')
		return (add_token(tokens, new_token(OUT, ">", NO)), (*line)++, 1);
	return (0);
}

static void	handle_word(t_token **tokens, char **line)
{
	char	*value;

	value = read_word(line);
	add_token(tokens, new_token(WORD, value, NO));
	free(value);
}

/*
** Lexer principal com melhor tratamento de erros
*/
t_token	*lexer(char *line)
{
	t_token	*tokens;
	char	*value;

	tokens = NULL;
	while (*line)
	{
		skip_whitespace(&line);
		if (!*line)
			break ;
		if (*line == '\'')
		{
<<<<<<< HEAD
			value = read_quote(&line, '\'');
			add_token(&tokens, new_token(WORD, value, SINGLE));
			free(value);
			continue ;
		}
		else if (*line == '"')
		{
			value = read_quote(&line, '"');
			add_token(&tokens, new_token(WORD, value, DOUBLE));
			free(value);
			continue ;
=======
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
>>>>>>> e4168d3bb3618b37a230190b7a6426e7f433554b
		}
		else if (handle_operators(&tokens, &line))
			continue ;
		handle_word(&tokens, &line);
	}
	return (tokens);
}
