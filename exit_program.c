#include "minishell.h"

void	sig_int(int code)
{
	(void)code;
	write(1, "\n", 1);	
	rl_on_new_line();
	rl_replace_line("", 1);
}

void	event_ctrl_c(void)
{
	struct sigaction sa;
	
	sa.sa_handler = sig_int; 
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
