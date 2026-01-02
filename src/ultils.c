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

void	free_shell(char *line, char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
	free(line);
}
