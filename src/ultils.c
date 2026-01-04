#include "../minishell.h"

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
			return (free_shell(NULL, new), NULL);
	return (new);
}

void	free_shell(t_shell *shell)
{
	int	i;

	if (shell->line)
		free(shell->line);
	t_token *tmp;
	while (shell->cmds)
	{
		tmp = shell->cmds;
		shell->cmds = shell->cmds->next;
		free(tmp->value);
		free(tmp);
	}
	if (shell->env)
	{
		i = 0;
		while (shell->env[i++])
			free(shell->env[i]);
		free(shell->env);
	}
}
