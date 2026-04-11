/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:32:33 by dedantas          #+#    #+#             */
/*   Updated: 2026/04/04 16:40:09 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	exec_single_builtin(t_shell *shell, t_cmd *cmd, pid_t *pids)
{
	free(pids);
	if (apply_redirs(cmd) != 0)
		return (1);
	shell->exit_status = exec_builtin(cmd, shell);
	return (shell->exit_status);
}

int	heredoc_stop(char *line, char *delimiter)
{
	if (!line)
		return (1);
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	create_process(t_cmd *cmd, int *pipe_fd, pid_t *pid)
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (cmd->next && pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	*pid = fork();
	if (*pid == -1)
		return (perror("fork"), 1);
	return (0);
}
