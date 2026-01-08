#include "../minishell.h"

int is_builtin(char *cmd_name)
{
    if (!cmd_name)
        return (0);
    if (ft_strcmp(cmd_name, "echo") == 0 ||
        ft_strcmp(cmd_name, "cd") == 0 ||
        ft_strcmp(cmd_name, "pwd") == 0 ||
        ft_strcmp(cmd_name, "export") == 0 ||
        ft_strcmp(cmd_name, "unset") == 0 ||
        ft_strcmp(cmd_name, "env") == 0 ||
        ft_strcmp(cmd_name, "exit") == 0)
        return (1);
    return (0);
}

int exec_builtin(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !cmd->args || !cmd->args[0])
        return (1);

    char *name = cmd->args[0];

    if (ft_strcmp(name, "echo") == 0)
        return (mini_echo(cmd));
    if (ft_strcmp(name, "pwd") == 0)
        return (mini_pwd(shell));
    if (ft_strcmp(name, "env") == 0)
        return (mini_env(shell));
    if (ft_strcmp(name, "exit") == 0)
        return (mini_exit(cmd, shell));  // sai do programa!
    if (ft_strcmp(name, "cd") == 0)
        return (mini_cd(cmd, shell));
    if (ft_strcmp(name, "export") == 0)
        return (mini_export(cmd, shell));
    if (ft_strcmp(name, "unset") == 0)
        return (mini_unset(cmd, shell));

    return (1);
}

int executor(t_shell *shell)
{
    if (!shell || !shell->cmds)
        return (0);

    t_cmd *cmd = shell->cmds;

    // Por agora assumimos 1 comando (sem pipes)
    if (is_builtin(cmd->args[0]))
        return (exec_builtin(cmd, shell));
    else
    {
        // Aqui virá o fork + execve mais tarde
        printf("Comando externo não implementado: %s\n", cmd->args[0]);
        return (127);
    }
}