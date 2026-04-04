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

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp(cmd_name, "echo") == 0
		|| ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0
		|| ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}

int	is_state_changing(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "cd") == 0 || ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0 || ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	name = cmd->args[0];
	if (ft_strcmp(name, "echo") == 0)
		return (mini_echo(cmd));
	if (ft_strcmp(name, "pwd") == 0)
		return (mini_pwd(shell));
	if (ft_strcmp(name, "env") == 0)
		return (mini_env(shell));
	if (ft_strcmp(name, "exit") == 0)
		return (mini_exit(cmd, shell));
	if (ft_strcmp(name, "cd") == 0)
		return (mini_cd(cmd, shell));
	if (ft_strcmp(name, "export") == 0)
		return (mini_export(cmd, shell));
	if (ft_strcmp(name, "unset") == 0)
		return (mini_unset(cmd, shell));
	return (1);
}

static int	handle_input(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return (perror(redir->file), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_output(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(redir->file), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(redir->file), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_heredoc(t_redir *redir)
{
	if (redir->heredoc_fd != -1)
	{
		dup2(redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
	}
	return (0);
}

static int	apply_redirs(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == IN && handle_input(redir))
			return (1);
		else if (redir->type == OUT && handle_output(redir))
			return (1);
		else if (redir->type == APPEND && handle_append(redir))
			return (1);
		else if (redir->type == HEREDOC && handle_heredoc(redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}

/*static int	apply_redirs(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1)
				return (perror(redir->file), 1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == OUT)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (perror(redir->file), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (perror(redir->file), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == HEREDOC && redir->heredoc_fd != -1)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
		}
		redir = redir->next;
	}
	return (0);
}*/

static char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_getenv(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (free_arr(paths), path);
		free(path);
	}
	return (free_arr(paths), NULL);
}

static int	wait_children(pid_t *pids, int n)
{
	int	i;
	int	status;
	int	last_status;

	last_status = 0;
	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
		i++;
	}
	return (last_status);
}

static int	count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

static int	has_real_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->args && cmd->args[0])
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

static int	exec_single_builtin(t_shell *shell, t_cmd *cmd, pid_t *pids)
{
	if (apply_redirs(cmd) != 0)
		return (free(pids), 1);
	shell->exit_status = exec_builtin(cmd, shell);
	free(pids);
	return (shell->exit_status);
}

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
		exit(1);
	if (is_builtin(cmd->args[0]) && !is_state_changing(cmd->args[0]))
		exit(exec_builtin(cmd, shell));
	path = find_path(cmd->args[0], shell->env);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	execve(path, cmd->args, shell->env);
	perror(cmd->args[0]);
	exit(127);
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
			if (cmd->next && pipe(pipe_fd) == -1)
				return (perror("pipe"), 1);
			pids[i] = fork();
			if (pids[i] == -1)
				return (perror("fork"), 1);
			if (pids[i] == 0)
				exec_child(cmd, shell, prev_fd, pipe_fd);
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
			else
				prev_fd = -1;
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

/*int	executor(t_shell *shell)
{
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	*pids;
	int		n;
	int		i;
	int		has_real_cmd;
	char	*path;

	if (!shell->cmds)
		return (1);
	cmd = shell->cmds;
	has_real_cmd = 0;
	while (cmd)
	{
		if (cmd->args && cmd->args[0])
			has_real_cmd = 1;
		cmd = cmd->next;
	}
	if (!has_real_cmd)
		return (0);
	n = count_cmds(shell->cmds);
	pids = malloc(sizeof(pid_t) * n);
	if (!pids)
		return (1);
	cmd = shell->cmds;
	if (n == 1 && cmd->args && is_builtin(cmd->args[0])
		&& is_state_changing(cmd->args[0]))
	{
		if (apply_redirs(cmd) != 0)
			return (free(pids), 1);
		shell->exit_status = exec_builtin(cmd, shell);
		free(pids);
		return (shell->exit_status);
	}
	prev_fd = -1;
	i = 0;
	cmd = shell->cmds;
	while (cmd)
	{
		if (!cmd->args || !cmd->args[0])
		{
			cmd = cmd->next;
			i++;
			continue ;
		}
		if (cmd->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			free(pids);
			return (1);
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			free(pids);
			return (1);
		}
		if (pids[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
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
			if (apply_redirs(cmd) != 0)
				exit(1);
			if (is_builtin(cmd->args[0]) && !is_state_changing(cmd->args[0]))
				exit(exec_builtin(cmd, shell));
			path = find_path(cmd->args[0], shell->env);
			if (!path)
			{
				ft_putstr_fd(cmd->args[0], STDERR_FILENO);
				ft_putendl_fd(": command not found", STDERR_FILENO);
				exit(127);
			}
			execve(path, cmd->args, shell->env);
			perror(cmd->args[0]);
			exit(127);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		else
			prev_fd = -1;
		cmd = cmd->next;
		i++;
	}
	shell->exit_status = wait_children(pids, n);
	free(pids);
	return (shell->exit_status);
}*/
