#ifndef MINISHEL_H
# define MINISHEL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <limits.h>

typedef enum e_type // enum para saber o tipo de token
{
	WORD,
	PIPE,	// |
	IN,	// <
	OUT,	 // >
	APPEND,	 // >>
	HEREDOC, // <<
} t_type;

typedef struct s_token // lista de tokens
{
	t_type		type;
	char		*value;
	struct s_token	*next;
} t_token;

typedef struct s_redir // lista de redirecionamento
{
	t_type		type;
	char		*file;      // nome do arquivo ou delimitador
	int		heredoc_fd; // fd de heredoc se type == HERE
	struct s_redir	*next;
} t_redir;

typedef struct s_cmd // lista de comandos
{
	char		**args;
	t_redir		*redirs;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_shell
{
	char	**env; // copia para manipulação
	char	*line; // linha de comando
	t_token *tokens;
	t_cmd	*cmds;
} t_shell;

char	**ft_envdup(char **arr);
void	free_shell(t_shell *shell);

// ultils
int	ft_strcmp(const char *s1, const char *s2);
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);

t_token	*lexer(char *line);
t_cmd	*parser(t_token *tokens);
int heredoc_handle(t_shell *shell);
int mini_pwd(t_shell *shell);               // pode precisar de env no futuro, por agora vazio
int mini_env(t_shell *shell);               // usa shell->env
int mini_echo(t_cmd *cmd);                  // só usa cmd->args
int mini_exit(t_cmd *cmd, t_shell *shell);  // precisa de args e free
int mini_cd(t_cmd *cmd, t_shell *shell);
int mini_export(t_cmd *cmd, t_shell *shell);
int mini_unset(t_cmd *cmd, t_shell *shell);

// Funções auxiliares (adiciona os protótipos para evitar implicit declaration)
int mini_env2(char **env);
void up_env_var(t_shell *shell, const char *str, int eq);
void export_error(char *arg);

// Executor e helpers
int executor(t_shell *shell);
int is_builtin(char *cmd_name);
int exec_builtin(t_cmd *cmd, t_shell *shell);

#endif
