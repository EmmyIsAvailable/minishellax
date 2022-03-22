#include "../minishell.h"

int	ft_cd(t_token *token, t_data *data)
{
	getcwd(data->oldpwd, 0);
	if (chdir(token->data) == -1)
		return (1);
	getcwd(data->pwd, 0);
	return (0);
}

int	dispatch_builtins(t_token *token, t_data *data)
{
	if (ft_strncmp(token->data, "echo", 5) == 0)
	{
		if (!token->next)
			return (displayOnTerm("\n"));
		return (ft_echo(token->next, data));
	}
	if (ft_strncmp(token->data, "pwd", 4) == 0 && !token->next)
		return (ft_pwd());
	if (ft_strncmp(token->data, "env", 4) == 0 && !token->next)
		return (ft_env(data));
	if (ft_strncmp(token->data, "cd", 3) == 0 && !token->next->next)
	{
		ft_cd(token->next, data);
		return (0);
	}
	if (ft_strncmp(token->data, "exit", 6) == 0 && !token->next)
	{
		//free les futurs trucs a free
		exit(0);
	}
	if (ft_strncmp(token->data, "export", 7) == 0)
		return (ft_export(cmd, data));
	/*if (ft_strncmp(token->data, "unset", 6) == 0 && cmd[1] != NULL)
	{	
		return (ft_unset(cmd, data));
	}*/
	return (1);
}
