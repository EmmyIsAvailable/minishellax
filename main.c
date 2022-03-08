#include "minishell.h"

int	init_data(t_data *data, char **envp)
{
	data->envp = envp;
	data->var = NULL;
	return (0);
}

int	tmp_pars(char **cmd, t_data *data) //parsing nul en attendant que tu fasses le vrai celuici juste pour mes tests
{
	int	i;

	i = 0;
	if (cmd[0] && !cmd[1])
	{
		while (cmd[0][i])
		{
			if (cmd[0][i] == '=')
			{
				if (!data->var)
					data->var = cmd[0];
				else
				{
					data->var = ft_strjoin(data->var, " ");
					data->var = ft_strjoin(data->var, cmd[0]);
				}
				return (0);
			}
			i++;
		}
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char	*history;
	t_data	data;
	char	**cmd;

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
		if (cmd != NULL)
			free(cmd);
		history = readline("> ");
		if (history == NULL) 
			break ;
		add_history(history);
		cmd = ft_split(history, ' ');
		if (cmd[0])
		{
			dispatch_builtins(cmd, &data);
			tmp_pars(cmd, &data);
		}
	}
	return (0);
}
