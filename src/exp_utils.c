/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 21:02:42 by dedantas          #+#    #+#             */
/*   Updated: 2026/04/07 21:03:39 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_value(t_shell *shell, char *name)
{
	char	*value;

	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(shell->exit_status));
	value = ft_getenv(shell->env, name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*append_char(char *result, char c)
{
	char	*tmp;
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	tmp = ft_strjoin(result, str);
	free(result);
	return (tmp);
}

char	*ex_handle_quotes(char *result, int *in_dquote)
{
	char	*tmp;

	tmp = ft_strjoin(result, "\"");
	free(result);
	*in_dquote = !(*in_dquote);
	return (tmp);
}

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp(cmd_name, "echo") == 0
		|| ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0
		|| ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}

int	is_state_changing(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "cd") == 0 || ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0 || ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}
