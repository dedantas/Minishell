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
		shell.tokens = lexer(shell.line);
		t_token *tmp = shell.tokens; //test
		while (tmp) //test
		{
			printf("Token: %d, Value: %s\n", tmp->type, tmp->value);
			tmp = tmp->next;
		}
		//exec_buitins(&shell);
		free_shell(&shell);
	}
	free_shell(&shell);
	return (0);
}
