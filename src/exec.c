/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilopes <vilopes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 21:13:44 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/17 19:43:01 by vilopes          ###   ########.fr       */
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

int is_state_changing(char *name)
{
	if (!name)
		return 0;
	if (ft_strcmp(name, "cd") == 0 || ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0 || ft_strcmp(name, "exit") == 0)
		return 1;
	return 0;
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

static int count_cmds(t_cmd *cmds)
{
	int count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

static char *find_path(char *cmd, char **env)
{
	char **paths;
	char *path;
	char *tmp;
	int i;

	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_getenv(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			free_arr(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_arr(paths);
	return (NULL);
}

static int apply_redirs(t_cmd *cmd)
{
	t_redir *redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == IN)
		{
			int fd = open(redir->file, O_RDONLY);
			if (fd == -1)
				return (perror(redir->file), 1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == OUT)
		{
			int fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (perror(redir->file), 1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == APPEND)
		{
			int fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
}

/*
** Executa um comando filho (builtin ou externo)
** prev_fd: stdin do comando anterior (pipe)
** next_fd: stdout do comando atual (pipe)
*/
static int exec_child(t_cmd *cmd, t_shell *shell, int prev_fd, int next_fd)
{
    if (prev_fd != STDIN_FILENO)
        dup2(prev_fd, STDIN_FILENO);
    if (next_fd != STDOUT_FILENO)
        dup2(next_fd, STDOUT_FILENO);

    if (apply_redirs(cmd) != 0)
        exit(1);

    if (is_builtin(cmd->args[0]) && !is_state_changing(cmd->args[0]))
        exit(exec_builtin(cmd, shell));

    char *path = find_path(cmd->args[0], shell->env);
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

/*
** Espera todos os filhos do pipeline e retorna exit status do último
*/
static int wait_children(pid_t *pids, int n)
{
    int i;
    int status;
    int last_status = 0;

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

/*
** Executor com suporte a pipelines e heredoc
*/
int executor(t_shell *shell)
{
    t_cmd *cmd;
    int pipe_fd[2];
    int prev_fd;
    pid_t *pids;
    int n;
    int i;

    if (!shell->cmds)
	    return (1);
    n = count_cmds(shell->cmds);
    pids = malloc(sizeof(pid_t) * n);
    if (!pids)
        return (1);

    i = 0;
    cmd = shell->cmds;
	if (n == 1 && is_builtin(cmd->args[0]) && is_state_changing(cmd->args[0]))
	{
		if (apply_redirs(cmd) != 0)
			return (free(pids), 1);
		shell->exit_status = exec_builtin(cmd, shell);
		return (free(pids), shell->exit_status);
	}
    prev_fd = STDIN_FILENO;
    while (cmd)
    {
        if (cmd->next)
            pipe(pipe_fd);
        else
        {
            pipe_fd[0] = STDIN_FILENO;
            pipe_fd[1] = STDOUT_FILENO;
        }

        pids[i] = fork();
        if (pids[i] == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            exec_child(cmd, shell, prev_fd, pipe_fd[1]);
        }

        if (prev_fd != STDIN_FILENO)
            close(prev_fd);
        if (pipe_fd[1] != STDOUT_FILENO)
            close(pipe_fd[1]);

        prev_fd = pipe_fd[0];
        cmd = cmd->next;
        i++;
    }
    shell->exit_status = wait_children(pids, n);
    return (free(pids), shell->exit_status);
}
