/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:58:02 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/12 19:02:58 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_pwd_env(t_shell *shell, const char *old)
{
	char	buf[PATH_MAX];
	int i;
	// OLDPWD
	i = 0;
	while (shell->env && shell->env[i] && ft_strncmp(shell->env[i], "OLDPWD=", 7) != 0)
		i++;
	if (shell->env && shell->env[i])
	{
		free(shell->env[i]);
		shell->env[i] = ft_strjoin("OLDPWD=", old ? old : "");
	}
	// PWD
	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		i = 0;
		while (shell->env && shell->env[i] && ft_strncmp(shell->env[i], "PWD=", 4) != 0)
			i++;
		if (shell->env && shell->env[i])
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("PWD=", buf);
		}
	}
}

static char	*ft_getenv(char **env, const char *name)
{
    int     i;
    size_t  len;

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

int mini_cd(t_cmd *cmd, t_shell *shell)
{
    char    old[PATH_MAX];
    char    *path;

    if (!cmd || !cmd->args || cmd->args[0] == NULL)
        return (1);

    if (cmd->args[2])  // too many args
        return (ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO), 1);

    if (getcwd(old, sizeof(old)) == NULL)
        return (perror("minishell: cd"), 1);

    if (!cmd->args[1] || ft_strcmp(cmd->args[1], "--") == 0)
        path = ft_getenv(shell->env, "HOME");
    else if (ft_strcmp(cmd->args[1], "-") == 0)
    {
        path = ft_getenv(shell->env, "OLDPWD");
        if (path)
            printf("%s\n", path);
    }
    else
        path = cmd->args[1];

    if (!path || !*path)
        return (ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO), 1);

    if (chdir(path) == -1)
    {
        ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
        perror(cmd->args[1]);
        return (1);
    }

    update_pwd_env(shell, old);
    return (0);
}

int mini_unset(t_cmd *cmd, t_shell *shell)
{
    int i, j, k, len;

    if (!cmd || !cmd->args || !shell || !shell->env)
        return (0);

    i = 1;
    while (cmd->args[i])
    {
        len = ft_strlen(cmd->args[i]);
        j = k = 0;
        while (shell->env[j])
        {
            if (ft_strncmp(shell->env[j], cmd->args[i], len) != 0 ||
                shell->env[j][len] != '=')
            {
                if (j != k)
                    shell->env[k++] = shell->env[j];
                else
                    k++;
            }
            else
                free(shell->env[j]);
            j++;
        }
        shell->env[k] = NULL;
        i++;
    }
    return (0);
}

int mini_export(t_cmd *cmd, t_shell *shell)
{
    int i, j, eq, valid;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (1);

    if (!cmd->args[1])
        return (mini_env2(shell->env));

    i = 1;
    while (cmd->args[i])
    {
        eq = 0;
        while (cmd->args[i][eq] && cmd->args[i][eq] != '=')
            eq++;

        if (eq == 0)
        {
            export_error(cmd->args[i]);
            i++;
            continue;
        }

        valid = 1;
        if (!ft_isalpha(cmd->args[i][0]) && cmd->args[i][0] != '_')
            valid = 0;

        j = 0;
        while (j < eq && valid)
        {
            if (!ft_isalnum(cmd->args[i][j]) && cmd->args[i][j] != '_')
                valid = 0;
            j++;
        }

        if (valid)
            up_env_var(shell, cmd->args[i], eq);
        else
            export_error(cmd->args[i]);

        i++;
    }
    return (0);
}
