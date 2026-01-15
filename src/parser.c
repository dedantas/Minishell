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
<<<<<<< HEAD
	redir->expand = expand;
	redir->next = NULL;
=======
	redir->next= NULL;
>>>>>>> e4168d3bb3618b37a230190b7a6426e7f433554b
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
<<<<<<< HEAD
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
=======
			add_arg(current, tokens->value);
		else if (is_redir(tokens->type))
		{
			if (!tokens->next || tokens->next->type != WORD)
				return (printf("syntax error\n"), NULL);
			add_redir(current, tokens->type, tokens->next->value);
			tokens = tokens->next;
		}
		else if (tokens->type == PIPE)
		{
			if (!current->args || !tokens->next)
				return (printf("syntax error near |\n"), NULL);
			current = NULL;
		}
		tokens = tokens->next;
	}
	if (current && !current->args)
		return (printf("syntax error near unexpected token `newline'\n"), NULL);
>>>>>>> e4168d3bb3618b37a230190b7a6426e7f433554b
	return (cmds);
}
