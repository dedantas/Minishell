#include "../minishell.h"

static void	update_pwd_env(t_shell *shell, const char *old)
{
	char	buf[PATH_MAX];
	int	i;

	i = 0;
	while (shell->envp[i] && ft_strncmp(shell->envp[i], "OLDPWD=", 7) != 0)
		i++;
	if (shell->envp[i])
	{
		free(shell->envp[i]);
		shell->envp[i] = ft_strjoin("OLDPWD=", old);
	}
	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		i = 0;
		while (shell->envp[i] && ft_strncmp(shell->envp[i], "PWD=", 4) != 0)
			i++;
		if (shell->envp[i])
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strjoin("PWD=", buf);
		}
	}
}

static char	*ft_getenv(char **envp, const char *name)
{
	int		i;
	size_t	len;

	if (!envp || !name)
		return (NULL);

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

int	mini_cd(char **args, t_shell *shell)
{
	char	old[PATH_MAX];
	char	*path;

	if (args[2])
		return (perror("minishell: cd: too many arguments"), 1);
	if (getcwd(old, sizeof(old)) == NULL)
		return (perror("minishell: cd"), 1);
	if (!args[1] || ft_strncmp(args[1], "--", 2) == 0)
		path = ft_getenv(shell->envp, "HOME");
	else if (ft_strncmp(args[1], "-", 1) == 0)
	{
		path = ft_getenv(shell->envp, "OLDPWD");
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
	{
		path = args[1];
		if (chdir(path) != 0)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			return (perror(args[1]), 1);
		}
	}
	update_pwd_env(shell, old);
	return (0);

}

int	mini_unset(t_shell *shell, char **args)
{
	int	i;
	int	j;
	int	k;
	int	len;

	if (!shell || !shell->envp || !args)
		return (0);

	i = 1;
	while (args[i])
	{
		len = ft_strlen(args[i]);
		j = 0;
		k = 0;

		while (shell->envp[j])
		{
			if (!(ft_strncmp(shell->envp[j], args[i], len) == 0
				&& shell->envp[j][len] == '='))
			{
				if (j != k)
					shell->envp[k] = shell->envp[j];
				k++;
			}
			else
				free(shell->envp[j]);
			j++;
		}
		shell->envp[k] = NULL;
		i++;
	}
	return (0);
}

int	mini_export(t_shell *shell, char **args)
{
	int	i;
	int	j;
	int	valid;
	int	eq;

	if (!args[1])
		return (mini_env2(shell->envp));
	i = 0;
	while (args[++i])
	{
		eq = 0;
		while (args[i][eq] && args[i][eq] != '=')
			eq++;
		if (eq > 0 && args[i][eq] == '=')
		{
			valid = 1;
			if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
				valid = 0;
			j = -1;
			while (++j < eq && valid)
				if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
					valid = 0;
			if (valid)
				up_env_var(shell, args[i], eq);
			else
				export_error(args[i]);
		}
		else if (eq == 0)
			export_error(args[i]);
	}
	return (0);
}
