/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 02:32:52 by dedantas          #+#    #+#             */
/*   Updated: 2026/04/04 14:42:33 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_env(t_shell *shell)
{
	int	i;

	if (!shell || !shell->env)
		return (1);
	if (shell->cmds && shell->cmds->args[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(shell->cmds->args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	i = 0;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

static int	is_valid_var_name(const char *str, int eq)
{
	int	j;

	if (eq == 0)
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	j = 0;
	while (j < eq)
	{
		if (!ft_isalnum(str[j]) && str[j] != '_')
			return (0);
		j++;
	}
	return (1);
}

static void	process_export_arg(t_shell *shell, char *arg)
{
	int	eq;

	eq = 0;
	while (arg[eq] && arg[eq] != '=')
		eq++;
	if (eq == 0)
	{
		if (is_valid_var_name(arg, ft_strlen(arg)))
		{
			if (find_env_index(shell->env, arg) == -1)
				up_env_var(shell, arg, ft_strlen(arg));
		}
		else
			export_error(arg);
		return ;
	}
	if (!is_valid_var_name(arg, eq))
	{
		export_error(arg);
		return ;
	}
	up_env_var(shell, arg, eq);
}

int	mini_export(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (!cmd->args[1])
		return (mini_env2(shell->env));
	i = 1;
	while (cmd->args[i])
	{
		process_export_arg(shell, cmd->args[i]);
		i++;
	}
	return (0);
}

void	unset_var(t_shell *shell, const char *name)
{
	int	i;
	int	k;
	int	len;

	k = 0;
	i = 0;
	len = ft_strlen(name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) != 0
			|| shell->env[i][len] != '=')
		{
			if (i != k)
				shell->env[k] = shell->env[i];
			k++;
		}
		else
			free(shell->env[i]);
		i++;
	}
	shell->env[k] = NULL;
}
