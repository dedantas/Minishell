#include "../minishell.h"

int	exec_buitins(t_shell *shell)
{
        if (!shell->cmds || !shell->cmds->args)
                return (1);
        if (ft_strncmp(shell->cmds->args[0], "exit", 4) == 0)
                return (mini_exit(shell), 0);
        if (ft_strncmp(shell->cmds->args[0], "echo", 4) == 0)
                return (mini_echo(shell->cmds->args), 0);
        if (ft_strncmp(shell->cmds->args[0], "cd", 2) == 0)
                return (mini_cd(shell->cmds->args, shell), 0);
        if (ft_strncmp(shell->cmds->args[0], "pwd", 3) == 0)
                return (mini_pwd(), 0);
        if (ft_strncmp(shell->cmds->args[0], "env", 3) == 0)
                return (mini_env(shell->env), 0);
        if (ft_strncmp(shell->cmds->args[0], "export", 6) == 0)
                return (mini_export(shell, shell->cmds->args), 0);
        if (ft_strncmp(shell->cmds->args[0], "unset", 5) == 0)
                return (mini_unset(shell, shell->cmds->args), 0);
        return (1);
}
