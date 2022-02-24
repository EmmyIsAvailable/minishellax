#include "minishell.h"

int main(int ac, char **av)
{
	char	*history;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("Error format : ./minishell\n", 1);
		return (1);
	}
	event_ctrl_c();
	while (1)
	{
		history = readline("> ");
		if (history == NULL) 
			break ;
		add_history(history);
	}
	return (0);
}
