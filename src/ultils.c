/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:24:50 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/15 01:59:59 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	skip_whitespace(char **line)
{
	while (**line && ft_isspace(**line))
		(*line)++;
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
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
	{
		new[i] = ft_strdup(arr[i]);
		if (!new[i])
			return (free_arr(new), NULL);
	}
	return (new);
}
