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

/*
REMOVER ESSE MAIN / VERIFICAR OUTROS FICHEIROS E FAZER PUSH
#include "../minishell.h"

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;

    t_shell shell = {0};
    shell.env = ft_envdup(envp);

    while (1)
    {
        shell.line = readline("🔹 minishell$ ");
        if (!shell.line)
        {
            printf("exit\n");
            break;
        }

        if (*shell.line)
            add_history(shell.line);

        shell.tokens = lexer(shell.line);

        // Debug tokens (mantém por agora)
        t_token *tmp = shell.tokens;
        while (tmp)
        {
            printf("Token: %d, Value: %s\n", tmp->type, tmp->value);
            tmp = tmp->next;
        }

        // === Simulação manual de t_cmd (até o parsing real entregar) ===
        t_cmd fake_cmd = {0};
        fake_cmd.args = ft_split(shell.line, ' ');  // separa por espaços (simples, mas funciona para testes)
        fake_cmd.infile = 0;   // stdin
        fake_cmd.outfile = 1;  // stdout
        fake_cmd.next = NULL;

        shell.cmds = &fake_cmd;

        // Agora executa!
        int status = executor(&shell);
        printf("Exit status: %d\n", status);  // para debug

        // Libera a simulação
        int j = 0;
        while (fake_cmd.args && fake_cmd.args[j])
            free(fake_cmd.args[j++]);
        free(fake_cmd.args);

        free_shell(&shell);  // libera tokens e line
    }

    // Free final do env
    int i = 0;
    while (shell.env && shell.env[i])
        free(shell.env[i++]);
    free(shell.env);

    return (0);
}
*/