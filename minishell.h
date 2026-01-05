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
	PIPE,	 // |
	IN,	 // <
	OUT,	 // >
	APPEND,	 // >>
	HEREDOC, // <<
	DOLLAR,  // $
} t_type;

typedef struct s_token // lista de tokens
{
	t_type		type;
	char		*value;
	struct s_token	*next;
} t_token;

typedef struct s_cmd // lista de comandos
{
	char		**args;
	int		infile;
	int		outfile;
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
/*int	exec_buitins(t_shell *shell);
int	mini_env(char **env);
int	mini_pwd(void);
int	mini_echo(char **cmd);
int	mini_exit(t_shell *shell);
int	mini_cd(char **args, t_shell *shell);
int	mini_unset(t_shell *shell, char **args);
int	mini_export(t_shell *shell, char **args);
int	mini_env2(char **envp);
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3);
void	add_env_var(t_shell *shell, const char *name, const char *value);
void	up_env_var(t_shell *shell, const char *str, int eq);
void	export_error(char *arg);*/
t_token	*lexer(char *line);

#endif
