/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:24:50 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/12 18:27:51 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i]);
	free(arr);
}

char	**ft_envdup(char **arr)
{
	char	**new;
	int		i;

	i = 0;
	while (arr && arr[i])
		i++;
	new = malloc(sizeof(*new) * (i + 1));
	if (!new)
		return (NULL);
	new[i] = NULL;
	while (i-- > 0)
		if (!(new[i] = ft_strdup(arr[i])))
			return (free_arr(new), NULL);
	return (new);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*cmd_tmp;
	t_redir	*redir_tmp;
	int		i;

	while (cmds)
	{
		cmd_tmp = cmds;
		cmds = cmds->next;
		if (cmd_tmp->args)
		{
			i = 0;
			while (cmd_tmp->args[i])
			{
				free(cmd_tmp->args[i]);
				i++;
			}
			free(cmd_tmp->args);
		}
		while (cmd_tmp->redirs)
		{
			redir_tmp = cmd_tmp->redirs;
			cmd_tmp->redirs = cmd_tmp->redirs->next;
			free(redir_tmp->file);
			free(redir_tmp);
		}
		free(cmd_tmp);
	}
}

void	free_shell(t_shell *shell)
{
	int	i;

	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cmds)
	{
		free_cmds(shell->cmds);
		shell->cmds = NULL;
	}
	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
		{
			free(shell->env[i]);
			i++;
		}
		free(shell->env);
		shell->env = NULL;
	}
}
