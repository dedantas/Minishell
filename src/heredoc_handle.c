/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:30:21 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/14 19:40:15 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static int g_signal = 0; // global para sinal do heredoc

// controle de sinais
void set_signal_mode(int mode)
{
	if (mode == 0) // ignore Ctrl-C
		signal(SIGINT, SIG_IGN);
	else if (mode == 1) // heredoc mode
		signal(SIGINT, [](int sig){ g_signal = sig; });
}

// código de saída do filho
static int child_exit_code(void)
{
	if (g_signal == SIGINT)
		return 128 + SIGINT;
	return EXIT_SUCCESS;
}*/

// filho lê o heredoc

static int	heredoc_stop(char *line, char *delimiter)
{
	if (!line)
		return (1);
	if (strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	child_heredoc(int pipe_fd[2], char *delimiter, int expand,
		t_shell *shell)
{
	char	*line;
	char	*out_line;

	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
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
	exit(EXIT_SUCCESS);
}

// pai espera e retorna fd de leitura
static int	parent_heredoc(int pipe_fd[2], pid_t pid)
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 128 + SIGINT)
	{
		close(pipe_fd[0]);
		return (1);
	}
	return (pipe_fd[0]);
}

// função principal
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
		exit(child_heredoc(pipe_fd, delimiter, expand, shell));
	else
		return (parent_heredoc(pipe_fd, pid));
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
			{
				redir->heredoc_fd = heredoc_read(shell, redir->file,
						redir->expand);
				if (redir->heredoc_fd == -1)
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
