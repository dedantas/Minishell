/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:45:34 by dedantas          #+#    #+#             */
/*   Updated: 2026/04/04 16:11:51 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_word(t_token **tokens, char **line)
{
	char	*value;

	value = read_word(line);
	add_token(tokens, new_token(WORD, value, NO));
	free(value);
}

static int	handle_single_quote(t_token **tokens, char **line)
{
	char	*value;

	value = read_quote(line, '\'');
	if (!value)
	{
		ft_putendl_fd("minishell: unclosed quote", 2);
		free_tokens(*tokens);
		return (0);
	}
	add_token(tokens, new_token(WORD, value, SINGLE));
	free(value);
	return (1);
}

static int	handle_double_quote(t_token **tokens, char **line)
{
	char	*value;

	value = read_quote(line, '"');
	if (!value)
	{
		ft_putendl_fd("minishell: unclosed quote", 2);
		free_tokens(*tokens);
		return (0);
	}
	add_token(tokens, new_token(WORD, value, DOUBLE));
	free(value);
	return (1);
}

static void	handle_word_or_operator(t_token **tokens, char **line)
{
	if (handle_operators(tokens, line))
		return ;
	handle_word(tokens, line);
}

t_token	*lexer(char *line, t_shell *shell)
{
	t_token	*tokens;

	tokens = NULL;
	while (*line)
	{
		skip_whitespace(&line);
		if (!*line)
			break ;
		if (*line == '\'')
		{
			if (!handle_single_quote(&tokens, &line))
				return (shell->exit_status = 2, NULL);
		}
		else if (*line == '"')
		{
			if (!handle_double_quote(&tokens, &line))
				return (shell->exit_status = 2, NULL);
		}
		else
			handle_word_or_operator(&tokens, &line);
	}
	return (tokens);
}
