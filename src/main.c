#include "../minishell.h"

int main(void)
{
    char    *line;
    while(1)
    {
        line = readline("🔹 minishell$ ");
        if (!line)
        {
            printf("exit\n");
            break;
        }
        if (*line)
            add_history(line);
        printf("Você digitou: %s\n", line);
        free(line);
    }

    return 0;
}