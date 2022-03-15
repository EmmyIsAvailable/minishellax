#include "../minishell.h"

int	ft_cd(char *cmd, t_data *data)
{
	getcwd(data->oldpwd, 0);
	if (chdir(cmd) == -1)
		return (1);
	getcwd(data->pwd, 0);
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
