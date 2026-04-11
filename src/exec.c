/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilopes <vilopes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 21:13:44 by dedantas          #+#    #+#             */
/*   Updated: 2026/04/04 18:39:20 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	setup_pipes(t_cmd *cmd, int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

static void	exec_child(t_cmd *cmd, t_shell *shell, int prev_fd, int *pipe_fd)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_pipes(cmd, prev_fd, pipe_fd);
	if (apply_redirs(cmd) != 0)
		e_exit(shell, 1);
	if (is_builtin(cmd->args[0]) && !is_state_changing(cmd->args[0]))
		e_exit(shell, exec_builtin(cmd, shell));
	path = find_path(cmd->args[0], shell->env);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		e_exit(shell, 127);
	}
	execve(path, cmd->args, shell->env);
	perror(cmd->args[0]);
	free(path);
	e_exit(shell, 127);
}

static void	update_fds(int *prev_fd, int pipe_fd[2], t_cmd *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
}

static int	exec_loop(t_shell *shell, pid_t *pids)
{
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_fd;
	int		i;

	cmd = shell->cmds;
	prev_fd = -1;
	i = 0;
	while (cmd)
	{
		if (cmd->args && cmd->args[0])
		{
			if (create_process(cmd, pipe_fd, &pids[i]))
				return (1);
			if (pids[i] == 0)
			{
				free(pids);
				exec_child(cmd, shell, prev_fd, pipe_fd);
			}
			update_fds(&prev_fd, pipe_fd, cmd);
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	executor(t_shell *shell)
{
	pid_t	*pids;
	int		n;

	if (!shell->cmds)
		return (1);
	if (!has_real_cmd(shell->cmds))
		return (0);
	n = count_cmds(shell->cmds);
	pids = malloc(sizeof(pid_t) * n);
	if (!pids)
		return (1);
	if (n == 1 && shell->cmds->args
		&& is_builtin(shell->cmds->args[0])
		&& is_state_changing(shell->cmds->args[0]))
		return (exec_single_builtin(shell, shell->cmds, pids));
	if (exec_loop(shell, pids) != 0)
		return (free(pids), 1);
	shell->exit_status = wait_children(pids, n);
	free(pids);
	return (shell->exit_status);
}
