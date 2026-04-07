/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:46:16 by dedantas          #+#    #+#             */
/*   Updated: 2026/04/04 16:32:04 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trim_whitespace(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	start = str;
	while (*start && ft_isspace(*start))
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && ft_isspace(*end))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len + 1);
	return (result);
}

static int	handle_pipe(t_cmd **current, t_token *tokens)
{
	if (!*current)
		return (0);
	if (!(*current)->args && !(*current)->redirs)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (0);
	}
	if (tokens->next && tokens->next->type == PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (0);
	}
	if (!tokens->next)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (0);
	}
	*current = NULL;
	return (1);
}

static int	process_token(t_cmd **current, t_token **tokens, t_cmd **cmds)
{
	if ((*tokens)->type == WORD)
		add_arg(*current, (*tokens)->value, (*tokens)->quote);
	else if (is_redir((*tokens)->type))
	{
		if (!handle_redir(*current, tokens))
		{
			free_cmds(*cmds);
			return (0);
		}
	}
	else if ((*tokens)->type == PIPE)
	{
		if (!handle_pipe(current, *tokens))
		{
			free_cmds(*cmds);
			return (0);
		}
	}
	return (1);
}

static int	check_empty_cmd(t_cmd *current, t_cmd *cmds)
{
	if (current && !current->args && !current->redirs)
	{
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `newline'", 2);
		free_cmds(cmds);
		return (0);
	}
	return (1);
}

t_cmd	*parser(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmds;
	t_cmd	*current;

	if (!tokens)
		return (NULL);
	cmds = NULL;
	current = NULL;
	while (tokens)
	{
		if (!current)
		{
			current = new_cmd();
			add_cmd(&cmds, current);
		}
		if (!process_token(&current, &tokens, &cmds))
			return (shell->exit_status = 2, NULL);
		tokens = tokens->next;
	}
	if (!check_empty_cmd(current, cmds))
		return (shell->exit_status = 2, NULL);
	return (cmds);
}
