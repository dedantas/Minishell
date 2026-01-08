#include "../minishell.h"

int mini_echo(t_cmd *cmd)
{
    int i = 1;
    int flag = 0;

    if (!cmd || !cmd->args)
        return (0);

    while (cmd->args[i] && cmd->args[i][0] == '-' && cmd->args[i][1] == 'n')
    {
        int j = 1;
        while (cmd->args[i][j] == 'n')
            j++;
        if (cmd->args[i][j] == '\0')
        {
            flag = 1;
            i++;
        }
        else
            break;
    }

    while (cmd->args[i])
    {
        printf("%s", cmd->args[i]);
        if (cmd->args[i + 1])
            printf(" ");
        i++;
    }
    if (!flag)
        printf("\n");

    return (0);
}

/*
int mini_pwd(t_shell *shell)
{
    char *path = getcwd(NULL, 0);
    if (!path)
    {
        perror("getcwd");
        return (1);
    }
    printf("%s\n", path);
    free(path);
    return (0);
}*/
int mini_pwd(t_shell *shell)
{
        (void)shell;
    char *path = getcwd(NULL, 0);
    if (!path)
    {
        perror("getcwd");
        return (1);
    }
    printf("%s\n", path);
    free(path);
    return (0);
}


int mini_env(t_shell *shell)
{
    int i = 0;
    if (!shell || !shell->env)
        return (1);

    while (shell->env[i] != NULL)
    {
        ft_putendl_fd(shell->env[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}

static  int     is_number(char *str)
{
        int     i;

        i = 0;
        if (str[i] == '-' || str[i] == '+')
                i++;
        if (!str[i])
                return (0);
        while (str[i])
        {
                if (!ft_isdigit(str[i]))
                        return (0);
                i++;
        }
        return (1);
}

int mini_exit(t_cmd *cmd, t_shell *shell)
{
    int exit_code = 0;

    if (!cmd || !cmd->args || !cmd->args[0])
        exit(0);

    if (!cmd->args[1])
    {
        // Sem argumento → exit com status atual (futuro: usar shell->last_status)
        exit(0);
    }

    if (cmd->args[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        return (1);  // Não sai do shell, só erro
    }

    if (!is_number(cmd->args[1]))
    {
        ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
        ft_putstr_fd(cmd->args[1], STDERR_FILENO);
        ft_putendl_fd(": numeric argument required", STDERR_FILENO);
        exit(255);
    }

    exit_code = ft_atoi(cmd->args[1]);
    exit_code = (exit_code % 256 + 256) % 256;  // garante 0-255

    // Libera tudo antes de sair (boa prática)
    free_shell(shell);
    exit(exit_code);
}
