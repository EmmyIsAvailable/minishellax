#include "minishell.h"

int main(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("Error format : ./minishell\n", 1);
		return (1);
	}
	readline("test> ");
	return (0);
}
