/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 02:19:41 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/15 02:23:03 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(t_type type, char *value, t_quote quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->quote = quote;
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

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->arg_quote = NULL;
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

void	add_arg(t_cmd *cmd, char *value, t_quote quote)
{
	int		i;
	int		j;
	char	**new;
	t_quote	*new_quote;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	new_quote = malloc(sizeof(t_quote) * (i * 2));
	j = -1;
	while (++j < i)
	{
		new[j] = cmd->args[j];
		new_quote[j] = cmd->arg_quote[j];
	}
	new[i] = ft_strdup(value);
	new[i + 1] = NULL;
	new_quote[i] = quote;
	free(cmd->args);
	free(cmd->arg_quote);
	cmd->args = new;
	cmd->arg_quote = new_quote;
}
