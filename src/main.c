/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:31:07 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/12 18:35:03 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_tokens(t_token *tokens)
{
    int i = 0;
    while (tokens)
    {
        printf("Token: %d, Value: %s\n", tokens->type, tokens->value);
        tokens = tokens->next;
        i++;
    }
}

void print_cmds(t_cmd *cmds)
{
    int i;
    int cmd_num = 0;
    t_redir *r;

    while (cmds)
    {
        printf("Cmd %d:\n", cmd_num);
        if (cmds->args)
        {
            i = 0;
            while (cmds->args[i])
	    {
                printf("  Arg[%d]: %s\n", i, cmds->args[i]);
		i++;
	    }
        }

        r = cmds->redirs;
        while (r)
        {
            printf("  Redir: type=%d, file=%s\n", r->type, r->file);
            r = r->next;
        }

        cmds = cmds->next;
        cmd_num++;
    }
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_shell	shell;
	shell.env = ft_envdup(envp);

	while (1)
	{
		shell.line = readline("🔹 minishell$ ");
		if (!shell.line)
			break; // Ctrl+D
		if (*shell.line)
			add_history(shell.line);

		// --- Lexer ---
		shell.tokens = lexer(shell.line);
		printf("🔹 Tokens before expansion:\n");
		print_tokens(shell.tokens);

		// --- Parser ---
		shell.cmds = parser(shell.tokens);
		if (!shell.cmds)
		{
			printf("⚠️ Parser error, skipping line\n");
			free_shell(&shell);
			continue;
		}
		// --- Test Heredoc ---
		if (heredoc_handle(&shell) != 0)
		{
			printf("⚠️ Heredoc error, skipping line\n");
			free_shell(&shell);
			continue;
		}

		// --- Print parsed commands ---
		print_cmds(shell.cmds);


		// --- Cleanup ---
		free_shell(&shell);
	}

	free_shell(&shell);
	return 0;
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
