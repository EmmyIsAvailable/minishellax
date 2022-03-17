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

int	tmp_pars(char **cmd, t_data *data) //parsing nul en attendant que tu fasses le vrai celuici juste pour mes tests
{
	int	i;
	int	j;
	int	k;

	j = -1;
	while (cmd[++j])
	{
		i = 1;
		k = 0;
		while (cmd[j][i])
		{	
			if (cmd[j][i] == '=')
			{
				if (!data->var)
					data->var[k] = cmd[j];
				else
				{
					while (data->var[k])
						k++;
					data->var[k] = cmd[j];
				}
				data->var[k + 1] = NULL;
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
//		if (cmd != NULL)
//			free(cmd);
		history = readline("> ");
		if (history == NULL) 
			break ;
		add_history(history);
		cmd = ft_split(history, ' ');
		if (cmd[0])
		{
			dispatch_builtins(cmd, &data);
			//tmp_pars(cmd, &data);
		}
	}
	return (0);
}
