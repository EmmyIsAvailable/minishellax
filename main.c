#include "minishell.h"

int	init_data(t_data *data, char **envp)
{
	data->envp = envp;
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char	*history;
	t_data	data;
	char	**cmd;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("Error format : ./minishell\n", 1);
		return (1);
	}
	init_data(&data, envp);
	event_ctrl_c();
	while (1)
	{
		if (cmd != NULL)
			free(cmd);
		history = readline("> ");
		if (history == NULL) 
			break ;
		add_history(history);
		cmd = ft_split(history, ' ');
		if (cmd[0])
			dispatch_builtins(cmd, &data);
	}
	return (0);
}
