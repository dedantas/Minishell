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

static char	*handle_dollar(t_shell *shell, char *str, int *i, char *result)
{
	int		start;
	char	*name;
	char	*value;
	char	*tmp;

	if (str[*i + 1] == '$' || !str[*i + 1] || (!ft_isalnum(str[*i + 1])
			&& str[*i + 1] != '_' && str[*i + 1] != '?'))
	{
		(*i)++;
		return (append_char(result, '$'));
	}
	(*i)++;
	start = *i;
	if (str[*i] == '?')
		(*i)++;
	else
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			(*i)++;
	name = ft_substr(str, start, *i - start);
	value = get_var_value(shell, name);
	tmp = ft_strjoin(result, value);
	free(result);
	free(name);
	free(value);
	return (tmp);
}

char	*expand_word(t_shell *shell, char *str)
{
	int		i;
	int		in_dquote;
	char	*result;

	i = 0;
	in_dquote = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '"')
			result = ex_handle_quotes(result, &in_dquote);
		else if (str[i] == '$')
		{
			result = handle_dollar(shell, str, &i, result);
			continue ;
		}
		else
			result = append_char(result, str[i]);
		i++;
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
