/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilopes <vilopes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:22:04 by dedantas          #+#    #+#             */
/*   Updated: 2026/04/04 16:44:10 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_var_value(t_shell *shell, char *name)
{
	char	*value;

	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(shell->exit_status));
	value = ft_getenv(shell->env, name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_word(t_shell *shell, char *str)
{
	int		i;
	char	*result;
	char	*tmp;
	int		in_dquote;
	int		start;
	char	*name;
	char	*value;
	//char	c[2];

	i = 0;
	result = ft_strdup("");
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '"' && !in_dquote)
		{
			tmp = ft_strjoin(result, "\"");
			free(result);
			result = tmp;
			in_dquote = 1;
			i++;
		}
		else if (str[i] == '"' && in_dquote)
		{
			tmp = ft_strjoin(result, "\"");
			free(result);
			result = tmp;
			in_dquote = 0;
			i++;
		}
		else if (str[i] == '$')
		{
			if (!str[i + 1] || (!ft_isalnum(str[i + 1])
					&& str[i + 1] != '_' && str[i + 1] != '?'))
			{
				tmp = ft_strjoin(result, "$");
				free(result);
				result = tmp;
				i++;
				continue ;
			}
			i++;
			start = i;
			if (str[i] == '?')
				i++;
			else
			{
				while (ft_isalnum(str[i]) || str[i] == '_')
					i++;
			}
			name = ft_substr(str, start, i - start);
			value = get_var_value(shell, name);
			tmp = ft_strjoin(result, value);
			free(result);
			result = tmp;
			free(name);
			free(value);
		}
		else
		{
			char c[2] = {str[i], 0};
			tmp = ft_strjoin(result, c);
			free(result);
			result = tmp;
			i++;
		}
	}
	return (result);
}

static void	expand_args(t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (cmd->arg_quote[i] != SINGLE)
		{
			expanded = expand_word(shell, cmd->args[i]);
			if (expanded)
			{
				free(cmd->args[i]);
				cmd->args[i] = expanded;
			}
		}
		i++;
	}
}

/*
** Expande redireções (ficheiros)
*/
static void	expand_redirs(t_shell *shell, t_cmd *cmd)
{
	t_redir	*redir;
	char	*expanded;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type != HEREDOC)
		{
			expanded = expand_word(shell, redir->file);
			if (expanded)
			{
				free(redir->file);
				redir->file = expanded;
			}
		}
		redir = redir->next;
	}
}

/*
** Função principal chamada após parser + heredoc_read
*/
int	expand(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		expand_args(shell, cmd);
		expand_redirs(shell, cmd);
		cmd = cmd->next;
	}
	return (0);
}
