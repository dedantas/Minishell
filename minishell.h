/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 02:43:18 by dedantas          #+#    #+#             */
/*   Updated: 2026/01/15 03:32:19 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <limits.h>

extern int g_exit_status;

typedef enum e_type // enum para saber o tipo de token
{
	WORD,
	PIPE,	// |
	IN,		// <
	OUT,	// >
	APPEND,	// >>
	HEREDOC,// <<
}	t_type;

typedef enum e_quote
{
	NO,
	SINGLE,
	DOUBLE,
}	t_quote;

typedef struct s_token // lista de tokens
{
	t_type		type;
	char		*value;
	t_quote		quote;
	struct		s_token					*next;
}	t_token;

typedef struct s_redir // lista de redirecionamento
{
	t_type		type;
	char		*file;
	int			heredoc_fd;
	int			expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd // lista de comandos
{
	char		**args;
	t_quote		*arg_quote;
	t_redir		*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**env; // copia para manipulação
	char	*line; // linha de comando
	t_token	*tokens;
	t_cmd	*cmds;
}	t_shell;

char	**ft_envdup(char **arr);

// ultils
int		is_operator(char c);
void	skip_whitespace(char **line);

// Lexer
t_token	*lexer(char *line);

// Parser
t_cmd	*parser(t_token *tokens);
int		heredoc_handle(t_shell *shell);

// Expanded
int		expand(t_shell *shell);
char	*expand_word(t_shell *shell, char *str);

// Buitins
int		mini_pwd(t_shell *shell);
int		mini_env(t_shell *shell);
int		mini_echo(t_cmd *cmd);
int		mini_exit(t_cmd *cmd, t_shell *shell);
int		mini_cd(t_cmd *cmd, t_shell *shell);
int		mini_export(t_cmd *cmd, t_shell *shell);
int		mini_unset(t_cmd *cmd, t_shell *shell);
int		mini_env2(char **env);
void	up_env_var(t_shell *shell, const char *str, int eq);
void	export_error(char *arg);
char	*ft_getenv(char **env, const char *name);
int		check_cd_args(t_cmd *cmd);
void	unset_var(t_shell *shell, const char *name);

// New _ add
t_token	*new_token(t_type type, char *value, t_quote quote);
void	add_token(t_token **tokens, t_token *new);
t_cmd	*new_cmd(void);
void	add_cmd(t_cmd **cmds, t_cmd *new);
void	add_arg(t_cmd *cmd, char *value, t_quote quote);

// Executor e helpers
int		executor(t_shell *shell);
int		is_builtin(char *cmd_name);
int		exec_builtin(t_cmd *cmd, t_shell *shell);

// Free
void	free_shell(t_shell *shell);
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
void	free_env(char **env);
void	free_arr(char **arr);

#endif
