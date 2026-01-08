#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while(s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i]);
	free(arr);
}

char	**ft_envdup(char **arr)
{
	char	**new;
	int		i;

	i = 0;
	while (arr && arr[i])
		i++;
	new = malloc(sizeof(*new) * (i + 1));
	if (!new)
		return (NULL);
	new[i] = NULL;
	while (i-- > 0)
		if (!(new[i] = ft_strdup(arr[i])))
			return (free_arr(new), NULL);
	return (new);
}

void	free_shell(t_shell *shell)
{
	int	i;
	t_token	*tmp;

	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	while (shell->tokens)
	{
		tmp = shell->tokens;
		shell->tokens = shell->tokens->next;
		free(tmp->value);
		free(tmp);
	}
	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
		{
			free(shell->env[i]);
			i++;
		}
		free(shell->env);
		shell->env = NULL;
	}
}
