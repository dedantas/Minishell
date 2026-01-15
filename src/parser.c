/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:46:16 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/15 18:58:22 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_redir(t_cmd *cmd, t_type type, char *file, int expand)
{
	t_redir	*redir;
	t_redir	*tmp;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->heredoc_fd = -1;
	redir->expand = expand;
	redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

int	is_redir(t_type type)
{
	return (type == IN || type == OUT
		|| type == APPEND || type == HEREDOC);
}

static int	handle_redir(t_cmd *current, t_token **tokens)
{
	int	do_expand;

	if (!(*tokens)->next || (*tokens)->next->type != WORD)
		return (0);
	do_expand = 1;
	if ((*tokens)->type == HEREDOC)
		do_expand = ((*tokens)->next->quote == NO);
	add_redir(current, (*tokens)->type,
		(*tokens)->next->value, do_expand);
	*tokens = (*tokens)->next;
	return (1);
}

static int	handle_pipe(t_cmd **current, t_token *tokens)
{
	if (!(*current)->args || !tokens->next)
		return (0);
	*current = NULL;
	return (1);
}

t_cmd	*parser(t_token *tokens)
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
		if (tokens->type == WORD)
			add_arg(current, tokens->value, tokens->quote);
		else if (is_redir(tokens->type)
			&& !handle_redir(current, &tokens))
			return (printf("syntax error"), NULL);
		else if (tokens->type == PIPE
			&& !handle_pipe(&current, tokens))
			return (printf("syntax error near |"), NULL);
		tokens = tokens->next;
	}
	if (current && !current->args)
		return (printf("syntax error near unexpected token `newline'"), NULL);
	return (cmds);
}
