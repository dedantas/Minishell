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
