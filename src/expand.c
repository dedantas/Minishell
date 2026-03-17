/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:22:04 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/14 19:26:09 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Expande $VAR ou $?
** NÃO suporta concatenação (mínimo exigido pela 42)
*/
char	*expand_word(t_shell *shell, char *str)
{
	char	*dollar;
	char	*var;
	char	*value;

	dollar = ft_strchr(str, '$');
	if (!dollar)
		return (ft_strdup(str));
	if (*(dollar + 1) == '?')
		return (0);
	var = ft_strdup(dollar + 1);
	if (!var)
		return (NULL);
	value = ft_getenv(shell->env, var);
	free(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

/*
** Expande argumentos do comando
*/
static void	expand_args(t_shell *shell, t_cmd *cmd)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		printf("[EXPAND ARG] before='%s'\n", cmd->args[i]);
		if (cmd->arg_quote[i] != SINGLE)
		{
			expanded = expand_word(shell, cmd->args[i]);
			if (expanded)
			{
				printf("[EXPAND ARG] after ='%s'\n", expanded);
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
		printf("[EXPAND REDIR] before='%s'\n", redir->file);
		if (redir->type != HEREDOC)
		{
			expanded = expand_word(shell, redir->file);
			if (expanded)
			{
				printf("[EXPAND REDIR] after ='%s'\n", expanded);
				free(redir->file);
				redir->file = expanded;
			}
		}
		redir = redir->next;
	}
}

/*
** Expansão do heredoc (se permitido)
*/
/*static int	expand_heredoc(t_shell *shell, t_redir *redir)
{
	char	*line;
	char	*expanded;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (1);
	line = get_next_line(redir->heredoc_fd);
	while (line)
	{
		printf("[HEREDOC] before='%s'\n", line);
		if (redir->expand)
			expanded = expand_word(shell, line);
		else
			expanded = ft_strdup(line);
		printf("[HEREDOC] after ='%s'\n", expanded);
		free(line);
		write(pipe_fd[1], expanded, ft_strlen(expanded));
		write(pipe_fd[1], "\n", 1);
		free(expanded);
		line = get_next_line(redir->heredoc_fd);
	}
	close(pipe_fd[1]);
	close(redir->heredoc_fd);
	redir->heredoc_fd = pipe_fd[0];
	return (0);
}*/

/*
** Função principal chamada após parser + heredoc_read
*/
int	expand(t_shell *shell)
{
	t_cmd	*cmd;
	//t_redir	*redir;

	cmd = shell->cmds;
	while (cmd)
	{
		expand_args(shell, cmd);
		expand_redirs(shell, cmd);
		/*redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC && redir->heredoc_fd != -1)
			{
				if (expand_heredoc(shell, redir))
					return (1);
			}
			redir = redir->next;
		}*/
		cmd = cmd->next;
	}
	return (0);
}
