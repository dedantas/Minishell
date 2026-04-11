/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:30:21 by dedantas          #+#    #+#             */
/*   Updated: 2026/04/04 16:42:17 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	child_heredoc(int pipe_fd[2], char *delimiter, int expand,
		t_shell *shell)
{
	char	*line;
	char	*out_line;

	close(pipe_fd[0]);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (heredoc_stop(line, delimiter))
			break ;
		if (expand)
			out_line = expand_word(shell, line);
		else
			out_line = ft_strdup(line);
		write(pipe_fd[1], out_line, ft_strlen(out_line));
		write(pipe_fd[1], "\n", 1);
		free(line);
		free(out_line);
	}
	close(pipe_fd[1]);
	free_shell(shell);
	free_env(shell->env);
	exit(EXIT_SUCCESS);
}

static int	parent_heredoc(int pipe_fd[2], pid_t pid)
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		close(pipe_fd[0]);
		return (-1);
	}
	return (pipe_fd[0]);
}

int	heredoc_read(t_shell *shell, char *delimiter, int expand)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
		child_heredoc(pipe_fd, delimiter, expand, shell);
	return (parent_heredoc(pipe_fd, pid));
}

static int	handle_single_heredoc(t_shell *shell, t_redir *redir)
{
	if (!redir->file || ft_strlen(redir->file) == 0)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
		return (1);
	}
	redir->heredoc_fd = heredoc_read(shell, redir->file, redir->expand);
	if (redir->heredoc_fd == -1)
	{
		shell->exit_status = 130;
		return (1);
	}
	return (0);
}

int	heredoc_handle(t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = shell->cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
				if (handle_single_heredoc(shell, redir))
					return (1);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
