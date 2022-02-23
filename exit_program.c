#include "minishell.h"

void	handler(__attribute__((unused))int dummy)
{
	exit(EXIT_SUCCESS);
}

void	event_ctrl_d(void)
{
	struct sigaction sa;
	
	sa.sa_handler = handler; 
	sa.sa_flags = 0;
	sigaction(EOF, &sa, NULL);
}
