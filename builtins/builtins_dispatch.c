#include "../minishell.h"

int	dispatch_builtins(char **cmd, t_data *data)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (ft_echo(&cmd[1]));
	if (ft_strncmp(cmd[0], "pwd", 4) == 0 && cmd[1] == NULL)
		return (ft_pwd());
	if (ft_strncmp(cmd[0], "env", 4) == 0 && cmd[1] == NULL)
		return (ft_env(data));
	if (ft_strncmp(cmd[0], "cd", 3) == 0 && cmd[2] == NULL)
		return (ft_cd(cmd[1]));
	if (ft_strncmp(cmd[0], "exit", 6) == 0 && cmd[1] == NULL)
	{
		//free les futurs trucs a free
		exit(0);
	}
	return (0);
}
