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

typedef struct s_shell
{
	char	**env; // GLOBAL
	char	**envp;
	char	**args;
	char	*line;
} t_shell;

char	**ft_envdup(char **arr);
void	free_shell(char *line, char **args);

#endif
