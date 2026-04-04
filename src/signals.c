#include "../minishell.h"

int g_signal = 0;

void handle_sigint(int sig)
{
    (void)sig;
    //g_signal = SIGINT;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
