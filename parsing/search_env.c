#include "../minishell.h"

int	ft_name(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (i);
	}
	return (i);
}

char	*ft_search_env(char *params, t_data *data)
{
	char	**envp;
	int		i;

	i = -1;
	envp = data->envp;
	while (envp[++i])
	{
		if (ft_strncmp(&envp[i][ft_name(params)], "=", 1) == 0)
		{
			if (ft_strncmp(envp[i], params, ft_name(params)) == 0)
				return (&envp[i][ft_name(params) + 1]);
		}
	}
	return (NULL);
}
