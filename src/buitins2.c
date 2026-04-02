/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:58:02 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/14 21:04:35 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_env_var(t_shell *shell, const char *varname,
			const char *value)
{
	int		i;
	char	*new_var;

	if (!shell || !shell->env || !varname)
		return ;
	i = 0;
	while (shell->env[i] && ft_strncmp(shell->env[i], varname,
			ft_strlen(varname)) != 0)
		i++;
	if (shell->env[i])
	{
		free(shell->env[i]);
		if (value)
			new_var = ft_strjoin(varname, value);
		else
			new_var = ft_strjoin(varname, "");
		shell->env[i] = new_var;
	}
}

static void	update_pwd_env(t_shell *shell, const char *old)
{
	char	buf[PATH_MAX];

	update_env_var(shell, "OLDPWD=", old);
	if (getcwd(buf, sizeof(buf)) != NULL)
		update_env_var(shell, "PWD=", buf);
}

char	*ft_getenv(char **env, const char *name)
{
	int		i;
	size_t	len;

	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "--") == 0)
		return (ft_getenv(shell->env, "HOME"));
	if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		path = ft_getenv(shell->env, "OLDPWD");
		if (path)
			printf("%s\n", path);
		else
			                        ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		return (path);
	}
	return (cmd->args[1]);
}

int	mini_cd(t_cmd *cmd, t_shell *shell)
{
	char	old[PATH_MAX];
	char	*path;

	if (check_cd_args(cmd))
		return (1);
	if (getcwd(old, sizeof(old)) == NULL)
		return (perror("minishell: cd"), 1);
	path = get_cd_path(cmd, shell);
	if (!path || !*path)
		return (ft_putstr_fd("minishell: cd: HOME not set\n",STDERR_FILENO), 1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(cmd->args[1]);
		return (1);
	}
	update_pwd_env(shell, old);
	return (0);
}
