#include "../minishell.h"

/*static int g_signal = 0; // global para sinal do heredoc

// controle de sinais
void set_signal_mode(int mode)
{
	if (mode == 0) // ignore Ctrl-C
		signal(SIGINT, SIG_IGN);
	else if (mode == 1) // heredoc mode
		signal(SIGINT, [](int sig){ g_signal = sig; });
}

// código de saída do filho
static int child_exit_code(void)
{
	if (g_signal == SIGINT)
		return 128 + SIGINT;
	return EXIT_SUCCESS;
}*/

// filho lê o heredoc
static int child_heredoc(t_shell *shell, int pipe_fd[2], char *delimiter)
{
	char *line;

//	set_signal_mode(1); // heredoc mode
	close(pipe_fd[0]); // fecha leitura

	while (1)
	{
		line = readline("> ");
		if (!line ) //|| g_signal == SIGINT)
		{
			free(line);
			break;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}

	close(pipe_fd[1]);
	free_shell(shell); // libera apenas shell->line, tokens e cmds se quiser
	exit(EXIT_FAILURE);
}

// pai espera e retorna fd de leitura
static int parent_heredoc(int pipe_fd[2], pid_t pid)
{
	int status;

	close(pipe_fd[1]); // fecha escrita
	waitpid(pid, &status, 0);

	if (WIFEXITED(status) && WEXITSTATUS(status) == 128 + SIGINT)
	{
		close(pipe_fd[0]);
		return 1;
	}
	return pipe_fd[0]; // fd para leitura do comando
}

// função principal
int heredoc_read(t_shell *shell, char *delimiter)
{
	pid_t pid;
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return 1;

	//set_signal_mode(0); // mãe ignora Ctrl-C

	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return 1;
	}
	if (pid == 0)
		exit(child_heredoc(shell, pipe_fd, delimiter));
	else
		return parent_heredoc(pipe_fd, pid);
}

int heredoc_handle(t_shell *shell)
{
	t_cmd *cmd;
	t_redir *redir;

	cmd = shell->cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				redir->heredoc_fd = heredoc_read(shell, redir->file);
				if (redir->heredoc_fd == -1)
					return (1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
