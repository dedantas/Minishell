/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:31:07 by dedantas          #+#    #+#             */
/*   Updated: 2026/04/04 16:12:52 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	shell->exit_status = 0;
	shell->env = ft_envdup(envp);
	setup_signals();
}

static void	process_line(t_shell *shell)
{
	if (!*shell->line)
		return ;
	add_history(shell->line);
	shell->tokens = lexer(shell->line);
	shell->cmds = parser(shell->tokens);
	if (!shell->cmds)
	{
		free_shell(shell);
		return ;
	}
	if (heredoc_handle(shell) != 0)
	{
		free_shell(shell);
		return ;
	}
	if (expand(shell) != 0)
	{
		free_shell(shell);
		return ;
	}
	executor(shell);
	free_shell(shell);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_shell(&shell, envp);
	while (1)
	{
		shell.line = readline("🔹 minishell$ ");
		if (!shell.line)
			break ;
		process_line(&shell);
	}
	free_shell(&shell);
	free_env(shell.env);
	return (0);
}

/*int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.exit_status = 0;
	shell.env = ft_envdup(envp);
	setup_signals();
	while (1)
	{
		shell.line = readline("🔹 minishell$ ");
		if (!shell.line)
			break ;
		if (*shell.line)
			add_history(shell.line);
		shell.tokens = lexer(shell.line);
		shell.cmds = parser(shell.tokens);
		if (!shell.cmds)
		{
			free_shell(&shell);
			continue ;
		}
		if (heredoc_handle(&shell) != 0)
		{
			free_shell(&shell);
			continue ;
		}
		if (expand(&shell) != 0)
		{
			free_shell(&shell);
			continue ;
		}
		executor(&shell);
		free_shell(&shell);
	}
	free_shell(&shell);
	free_env(shell.env);
	return (0);
}*/
