#ifndef MINISHEL_H
# define MINISHEL_H

#include <readline/readline.h>
#include <readline/history.h>

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct s_shell
{
    char **env; // GLOBAL
} t_shell;

#endif