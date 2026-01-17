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

void	print_tokens(t_token *t)
{
	while (t)
	{
		printf("	[TOKEN] type=%d value='%s' quote=%d\n",
			t->type, t->value, t->quote);
		t = t->next;
	}
}

void	print_cmds(t_cmd *cmd)
{
	int		i;
	int		n;
	t_redir	*r;

	n = 0;
	while (cmd)
	{
		printf("	Cmd %d:\n", n);
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("	arg[%d] = '%s' (quote=%d)\n",
					i, cmd->args[i], cmd->arg_quote[i]);
				i++;
			}
		}
		r = cmd->redirs;
		while (r)
		{
			printf("	redir type=%d file='%s' expand=%d fd=%d\n",
				r->type, r->file, r->expand, r->heredoc_fd);
			r = r->next;
		}
		cmd = cmd->next;
		n++;
	}
}

int	main(int ac, char **av, char **envp)
{
	// FALTA CHAMAR O EXECUTOR PARA RODAR OS BUILTINS (echo, cd, cat...)
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = ft_envdup(envp);
	int g_exit_status = 0;
	
	while (1)
	{
		shell.line = readline("🔹 minishell$ ");
		if (!shell.line)
			break ;
		if (*shell.line)
			add_history(shell.line);
		shell.tokens = lexer(shell.line);
		//printf("	1.Tokens before expansion:\n");
		//print_tokens(shell.tokens);
		shell.cmds = parser(shell.tokens);
		if (!shell.cmds)
		{
			//printf("	⚠️ Parser error, skipping line\n");
			g_exit_status = 2;
			free_shell(&shell);
			continue ;
		}
		if (heredoc_handle(&shell) != 0)
		{
			//printf("	⚠️ Heredoc error, skipping line\n");
			g_exit_status = 1;
			free_shell(&shell);
			continue ;
		}
		//printf("	2.After heredoc_handle:\n");
		//print_cmds(shell.cmds);
		if (expand(&shell) != 0)
		{
			//printf("	⚠️ Expand error\n");
			g_exit_status = 1;
			free_shell(&shell);
			continue ;
		}
		//printf("	3.After expand:\n");
		//print_cmds(shell.cmds);
		//printf("\n\n");
		g_exit_status = executor(&shell);
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
        fake_cmd.args = ft_split(shell.line, ' ');
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
