#include "../minishell.h"

int	displayOnTerm(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
	return (1);
}

int	variables_in_echo(char *params, t_data *data)
{
	char	**envp;
	int	i;

	i = 0;
	envp = data->envp;
	while (envp[i])
	{
		if (ft_strncmp(&envp[i][ft_strlen(params)], "=", 1) == 0)
		{
			if (ft_strncmp(envp[i], params, ft_strlen(params)) == 0)
			{
				displayOnTerm(&envp[i][ft_strlen(params) + 1]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_echo(char **params, t_data *data)
{
	int	i;
	int	option;
	int	print;

	i = 0;
	option = 0;
	print = 0;
	if (ft_strncmp(params[0], "-n", 3) == 0)
	{
		option = 1;
		i = 1;
	}
	while (params[i])
	{
		if (params[i][0] == '$')
			print = variables_in_echo(&params[i][1], data);
		else
			print = displayOnTerm(params[i]);
		if (params[i + 1] != NULL && print != 0)
			displayOnTerm(" ");
		i++;
	}
	if (option == 0)
		displayOnTerm("\n");
	return (0);
}

int	ft_env(t_data *data)
{
	char	**envp;
	int	i;

	i = 0;
	envp = data->envp;
	while (envp[i++])
		printf("%s\n", envp[i]);
	return (0);
}

int	ft_pwd(void)
{
	displayOnTerm(getcwd(NULL, 0));
	displayOnTerm("\n");
	return (0);
}
