/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedantas <dedantas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 02:43:18 by dedantas          #+#    #+#             */
/*   Updated: 2026/04/04 17:00:25 by dedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <limits.h>

extern int	g_signal;

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
	t_type			type;
	char			*value;
	t_quote			quote;
	struct s_token	*next;
}	t_token;

typedef struct s_redir // lista de redirecionamento
{
	t_type			type;
	char			*file;
	int				heredoc_fd;
	int				expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd // lista de comandos
{
	char			**args;
	t_quote			*arg_quote;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**env; // copia para manipulação
	char	*line; // linha de comando
	t_token	*tokens;
	t_cmd	*cmds;
	int		exit_status;
	int		s_exit;
}	t_shell;

char	**ft_envdup(char **arr);

// ultils
int		is_operator(char c);
void	skip_whitespace(char **line);
void	setup_signals(void);
int		heredoc_stop(char *line, char *delimiter);
int		handle_input(t_redir *redir);
int		handle_output(t_redir *redir);
int		handle_append(t_redir *redir);
int		handle_heredoc(t_redir *redir);
int		par_handle_heredoc(t_cmd *current, t_token *token);

// Lexer
t_token	*lexer(char *line, t_shell *shell);
char	*read_word(char **line);
char	*read_quote(char **line, char quote);
int		handle_operators(t_token **tokens, char **line);

// Parser
t_cmd	*parser(t_token *tokens, t_shell *shell);
int		heredoc_handle(t_shell *shell);
int		is_redir(t_type type);
int		handle_redir(t_cmd *current, t_token **tokens);
char	*trim_whitespace(char *str);

// Expanded
int		expand(t_shell *shell);
char	*expand_word(t_shell *shell, char *str);
char	*append_char(char *result, char c);
char	*get_var_value(t_shell *shell, char *name);
void	handle_quotes(char **line, int *in_quote, char *quote_char);
char	*ex_handle_quotes(char *result, int *in_dquote);

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
int		find_env_index(char **name, char *env);

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
int		is_state_changing(char *name);
int		apply_redirs(t_cmd *cmd);
char	*find_path(char *cmd, char **env);
int		has_real_cmd(t_cmd *cmd);
int		count_cmds(t_cmd *cmds);
int		exec_single_builtin(t_shell *shell, t_cmd *cmd, pid_t *pids);
int		wait_children(pid_t *pids, int n);
int		create_process(t_cmd *cmd, int *pipe_fd, pid_t *pid);

// Free
void	free_shell(t_shell *shell);
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
void	free_env(char **env);
void	free_arr(char **arr);
void	e_exit(t_shell *shell, int code);

#endif
