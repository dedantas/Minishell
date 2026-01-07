#include "../minishell.h"

int     mini_echo(char **cmd)
{
        int     i;
        int     flag;

        i = 1;
        flag = 0;
        while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
        {
                int     j = 1;
                while (cmd[i][j] == 'n')
                        j++;
                if (cmd[i][j] == '\0')
                {
                        flag = 1;
                        i++;
                }
                else
                        break ;
        }
        while (cmd[i])
        {
                printf("%s", cmd[i]);
                if (cmd[i + 1])
                        printf(" ");
                i++;
        }
        if (!flag)
                printf("\n");
        return (0);
}

int     mini_pwd(void)
{
        char *path;

        path = getcwd(NULL, 0);
        if (!path)
                return (1);
        printf("%s\n", path);
        free(path);
        return (0);
}

int     mini_env(char **env)
{
        int     i;

        i = 0;
        while (env[i] != NULL)
                ft_putendl_fd(env[i++], STDOUT_FILENO);
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

int     mini_exit(t_shell *shell)
{
        int     exit_code;

        if (!shell->args[1])
                exit_code = 0;
        else
        {
                if (shell->args[2])
                {
                        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
                        return (1);
                }
                if (!is_number(shell->args[1]))
                {
                        printf("minishell: exit: %s: numeric argument required\n", shell->args[1]);
                        exit_code = 2;
                }
                else
                {
                        exit_code = ft_atoi(shell->args[1]);
                        // Limitar a 0-255 como bash
                        if (exit_code < 0)
                                exit_code = 256 + (exit_code % 256);
                        else if (exit_code > 255)
                                exit_code = exit_code % 256;
                }
        }
        free_shell(shell->line, shell->args);
        exit(exit_code);
}
