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

typedef struct s_shell
{
	char	**env; // GLOBAL
	char	**envp;
	char	**args;
	char	*line;
} t_shell;

char	**ft_envdup(char **arr);
void	free_shell(char *line, char **args);
int	exec_buitins(t_shell *shell);
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
void	export_error(char *arg);

#endif
