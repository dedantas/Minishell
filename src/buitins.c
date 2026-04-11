/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:50:25 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/14 20:07:24 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	n_flag(char **args, int *i)
{
	int	j;
	int	flag;

	flag = 0;
	while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n')
	{
		j = 1;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] != '\0')
			break ;
		flag = 1;
		(*i)++;
	}
	return (flag);
}

int	mini_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	if (!cmd || !cmd->args)
		return (0);
	i = 1;
	flag = n_flag(cmd->args, &i);
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}

int	mini_pwd(t_shell *shell)
{
	char	*path;

	(void)shell;
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	mini_exit(t_cmd *cmd, t_shell *shell)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (shell->exit_status = 1, 1);
	}
	if (cmd->args[1] && !is_number(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		shell->exit_status = 255;
		shell->s_exit = 1;
		return (255);
	}
	if (cmd->args[1])
		shell->exit_status = (ft_atoi(cmd->args[1]) % 256 + 256) % 256;
	shell->s_exit = 1;
	return (shell->exit_status);
}
