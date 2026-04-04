/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:31:07 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/15 19:08:42 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **envp)
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
		/*if (g_signal == SIGINT)
		{
			shell.exit_status = 130;
			g_signal = 0;
			free(shell.line);	
		}*/
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
}
