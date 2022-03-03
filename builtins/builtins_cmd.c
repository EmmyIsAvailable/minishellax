#include "../minishell.h"

int	displayOnTerm(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
	return (0);
}

int	ft_echo(char **params)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (!params[0])
		return (0);
	if (ft_strncmp(params[0], "-n", 3) == 0)
	{
		option = 1;
		i = 1;
	}
	while (params[i])
	{
		displayOnTerm(params[i]);
		if (params[i + 1] != NULL)
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

int	ft_cd(char *path)
{
	if (chdir(path) != 0)
		return (1);
	return (0);
}
