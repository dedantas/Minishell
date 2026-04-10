/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:31:07 by dedantas          #+#    #+#             */
/*   Updated: 2026/04/07 20:56:54 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	e_exit(t_shell *shell, int code)
{
	free_shell(shell);
	free_env(shell->env);
	exit(code);
}

static void	increment_shlvl(t_shell *shell)
{
	char	*shlvl_str;
	char	*new_value;
	char	*var_entry;
	int		level;

	shlvl_str = ft_getenv(shell->env, "SHLVL");
	if (!shlvl_str || ft_strlen(shlvl_str) == 0)
		level = 0;
	else
		level = ft_atoi(shlvl_str);
	if (level < 0)
		level = 0;
	level++;
	if (level > 1000)
		level = 1;
	new_value = ft_itoa(level);
	var_entry = ft_strjoin("SHLVL=", new_value);
	up_env_var(shell, var_entry, ft_strlen("SHLVL"));
	free(new_value);
	free(var_entry);
}

static void	init_shell(t_shell *shell, char **envp)
{
	shell->exit_status = 0;
	shell->s_exit = 0;
	shell->env = ft_envdup(envp);
	shell->line = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	increment_shlvl(shell);
	setup_signals();
}

static void	process_line(t_shell *shell)
{
	if (!shell->line || !*shell->line)
		return ;
	add_history(shell->line);
	shell->tokens = lexer(shell->line, shell);
	shell->cmds = parser(shell->tokens, shell);
	if (shell->cmds && !heredoc_handle(shell) && !expand(shell))
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
		if (shell.s_exit)
			break ;
	}
	free_shell(&shell);
	free_env(shell.env);
	rl_clear_history();
	return (shell.exit_status);
}
