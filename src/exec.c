/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilopes <vilopes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 21:13:44 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/17 18:51:24 by vilopes          ###   ########.fr       */
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

int executor(t_shell *shell)
{
	t_cmd *cmd = shell->cmds;
	int num_cmds = count_cmds(cmd);

	if (num_cmds == 1)
	{
		if (is_builtin(cmd->args[0]))
			return (exec_builtin(cmd, shell));  // Builtin no parent (sem fork)
		else
		{
			pid_t pid = fork();
			if (pid == -1)
				return (1);
			if (pid == 0)
			{
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
			int status;
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
			if (WIFSIGNALED(status))
				return (128 + WTERMSIG(status));
			return (1);
		}
	}
	else
	{
		printf("Pipelines nao implementados ainda!\n");  // Placeholder para pipes
		return (1);
	}
}