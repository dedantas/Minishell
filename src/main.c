#include "../minishell.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell	shell;

	shell.envp = ft_envdup(envp);
	while(1)
	{
		shell.line = readline("🔹 minishell$ ");
		if (!shell.line)
		{
			printf("exit\n");
			break ;
		}
		if (shell.line)
		{
			shell.args = ft_split(shell.line, ' ');
			exec_buitins(&shell);
			add_history(shell.line);
		}
		free_shell(shell.line, shell.args);
	}

    return (0);
}
