#include "../minishell.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell	shell;

	shell.env = ft_envdup(envp);
	while(1)
	{
		shell.line = readline("🔹 minishell$ ");
		add_history(shell.line);
		shell.cmds = lexer(shell.line);
		exec_buitins(&shell);
		free_shell(&shell);
	}
	free_shell(&shell);
	return (0);
}
