#include "../minishell.h"

int	mini_env2(char **envp)
{
	int		i;
	char	*eq_pos;
	
	i = 0;
	while (envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			write(STDOUT_FILENO, envp[i], eq_pos - envp[i] + 1);
			ft_putchar_fd('"', STDOUT_FILENO);
			ft_putstr_fd(eq_pos + 1, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*result;
	
	if (!s1 || !s2 || !s3)
		return (NULL);
	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

void	add_env_var(t_shell *shell, const char *name, const char *value)
{
	int		j;
	int		count;
	char	**new_env;
	char	*new_var;
	
	if (!shell || !shell->envp || !name)
		return;
	count = 0;
	while (shell->envp[count])
		count++;
	new_var = ft_strjoin3(name, "=", value);
	if (!new_var)
		return;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		free(new_var);
		return;
	}
	j = -1;
	while (j++ < count)
		new_env[j] = shell->envp[j];
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free(shell->envp);
	shell->envp = new_env;
}

void	up_env_var(t_shell *shell, const char *str, int eq)
{
	int		i;
	char	*new_var;
	char	*name;
	char	*value;

	if (!shell || !shell->envp || !str || eq <= 0)
		return ;
	name = ft_substr(str, 0, eq);
	value = ft_strdup(str + eq + 1);
	new_var = ft_strjoin3(name, "=", value);
	if (!new_var || !name || !value)
	{
		free(name);
		free(value);
		return ;
	}
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, ft_strlen(name)) == 0
			&& shell->envp[i][ft_strlen(name)] == '=')
		{
			free(shell->envp[i]);
			shell->envp[i] = new_var;
			free(name);
			free(value);
			return ;
		}
		i++;
	}
	add_env_var(shell, name, value);
	free(new_var);
	free(name);
	free(value);
}

void	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}
