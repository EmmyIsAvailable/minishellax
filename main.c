#include "minishell.h"

int	init_data(t_data *data, char **envp)
{
	data->envp = envp;
	data->var = malloc(sizeof(char **) * 3);
	data->var[0] = ft_strdup("oui=0");
	data->var[1] = ft_strdup("non=1");
	data->var[2] = NULL;
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char	*history;
	t_data	data;
	t_token	*head;
//	char	**cmd;

	(void)av;
	history = NULL;
	if (ac != 1)
	{
		ft_putstr_fd("Error format : ./minishell\n", 1);
		return (1);
	}
	init_data(&data, envp);
	event_ctrl_c();
	while (1)
	{
//		if (cmd != NULL)
//			free(cmd);
		head = NULL;
		history = readline("> ");
		if (history == NULL) 
			break ;
		if (ft_parse(history, &head) == 1)
			exit(EXIT_FAILURE);
		ft_print(head);
		add_history(history);
/*		cmd = ft_split(history, ' ');
		if (cmd[0])
		{
			dispatch_builtins(cmd, &data);
			//tmp_pars(cmd, &data);
		}*/
	}
	return (0);
}
