/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:14:31 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/14 20:37:47 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_env2(char **env)
{
	int		i;
	char	*eq_pos;

	i = 0;
	while (env[i])
	{
		eq_pos = ft_strchr(env[i], '=');
		if (eq_pos)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			write(STDOUT_FILENO, env[i], eq_pos - env[i] + 1);
			ft_putchar_fd('"', STDOUT_FILENO);
			ft_putstr_fd(eq_pos + 1, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}

int	find_env_index(char **env, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0
			&& env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	add_env_var_raw(t_shell *shell, char *new_var)
{
	int		count;
	char	**new_env;

	count = 0;
	while (shell->env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return ;
	count = 0;
	while (shell->env[count])
	{
		new_env[count] = shell->env[count];
		count++;
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
}

void	up_env_var(t_shell *shell, const char *str, int eq)
{
	int		index;
	char	*name;
	char	*value;
	char	*new_var;

	if (!shell || !shell->env || !str || eq <= 0)
		return ;
	name = ft_substr(str, 0, eq);
	value = ft_strdup(str + eq + 1);
	new_var = ft_strjoin3(name, "=", value);
	if (!name || !value || !new_var)
		return (free(name), free(value), free(new_var));
	index = find_env_index(shell->env, name);
	if (index >= 0)
	{
		free(shell->env[index]);
		shell->env[index] = new_var;
	}
	else
		add_env_var_raw(shell, new_var);
	free(name);
	free(value);
}

int	mini_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!cmd || !cmd->args || !shell || !shell->env)
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		unset_var(shell, cmd->args[i]);
		i++;
	}
	return (0);
}
