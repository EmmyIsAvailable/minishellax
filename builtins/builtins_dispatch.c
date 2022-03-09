#include "../minishell.h"

int	ft_unset(char **cmd, t_data *data)
{
	char	**envp;
	int	i;
	int	j;

	j = 0;
	envp = data->envp;
	while (cmd[++j])
	{
		i = -1;
		while (envp[++i])
		{
			if (ft_strncmp(&envp[i][ft_strlen(cmd[j])], "=", 1) == 0)
			{
				if (ft_strncmp(envp[i], cmd[j], ft_strlen(cmd[j])) == 0)
				{
					while (envp[i])
					{	
						envp[i] = envp[i + 1];
						i++;
					}
				}
			}
		}
	}
	return (0);
}

void	add_var_envp(char *cmd, t_data *data)
{
	int	i;
	char	**envp;

	i = 0;
	envp = data->envp;
	while (envp[i])
		i++;
	envp[i] = cmd;
	envp[i + 1] = NULL;
}

int	ft_export(char **cmd, t_data *data)
{
	int	i;
	int	j;
	int	is_var;

	i = 1;
	while (cmd[i])
	{
		j = 1;
		is_var = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '=' && cmd[i][j + 1] != '\0')
				is_var = 1;
			j++;
		}
		if (is_var == 1)
			add_var_envp(cmd[i], data);
		i++;
	}
	return (0);
}

int	dispatch_builtins(char **cmd, t_data *data)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
	{
		if (!cmd[1])
			return (displayOnTerm("\n"));
		return (ft_echo(&cmd[1], data));
	}
	if (ft_strncmp(cmd[0], "pwd", 4) == 0 && cmd[1] == NULL)
		return (ft_pwd());
	if (ft_strncmp(cmd[0], "env", 4) == 0 && cmd[1] == NULL)
		return (ft_env(data));
	if (ft_strncmp(cmd[0], "cd", 3) == 0 && cmd[2] == NULL)
	{
		chdir(cmd[1]);
		return (0);
	}
	if (ft_strncmp(cmd[0], "exit", 6) == 0 && cmd[1] == NULL)
	{
		//free les futurs trucs a free
		exit(0);
	}
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (ft_export(cmd, data));
	if (ft_strncmp(cmd[0], "unset", 6) == 0 && cmd[1] != NULL)
	{	
		return (ft_unset(cmd, data));
	}
	return (0);
}
