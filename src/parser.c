/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:46:16 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/12 18:49:16 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*cmds)
		*cmds = new;
	else
	{
		tmp = *cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_arg(t_cmd *cmd, char *value)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	j = -1;
	while (++j < i)
		new[j] = cmd->args[j];
	new[i] = ft_strdup(value);
	new[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new;
}

void	add_redir(t_cmd *cmd, t_type type, char *file)
{
	t_redir	*redir;
	t_redir	*tmp;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->next= NULL;
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

int is_redir(t_type type)
{
    return (type == IN || type == OUT
        || type == APPEND || type == HEREDOC);
}

t_cmd *parser(t_token *tokens)
{
	t_cmd   *cmds = NULL;
	t_cmd   *current = NULL;

	if (!tokens)
		return NULL;
	while (tokens)
	{
		if (!current)
		{
			current = new_cmd();
			add_cmd(&cmds, current);
		}
		if (tokens->type == WORD)
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
			if (!current->args || !tokens->next || tokens->next->type == PIPE)
				return (printf("syntax error near |\n"), NULL);
			current = NULL;
		}
		tokens = tokens->next;
	}
	return (cmds);
}
