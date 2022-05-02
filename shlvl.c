#include "./minishell.h"

int	ft_export_prev(char *str, t_token *shlvl, t_data *data)
{
	t_token	*tmp;

	tmp = shlvl;
	while (tmp)
	{
		if (tmp->cmd_env == 0 && (int)ft_strlen(str) == ft_name(tmp->data))
			if (ft_strncmp(tmp->data, str, ft_strlen(str)) == 0)
			{
				ft_export(tmp, data);
				break ;
			}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset_prev(char *str, t_data *data)
{
	int	i;
	char	**envp;
	char	*to_export;

	i = 0;
	to_export = (char *)malloc(sizeof(char) * (ft_name(str) + 1));
	if (!to_export)
		return (1);
	while (str[i] != '=')
	{
		to_export[i] = str[i];
		i++;
	}
	to_export[i] = '\0';
	envp = data->envp;
	i = -1;
	while (envp[++i])
	{
		if (check_existence(to_export, envp[i]) == 1)
		{
			while (envp[i] && envp[i + 1])
			{
				envp[i] = ft_strdup(envp[i + 1]);
				i++;
			}
			free(envp[i]);
			envp[i] = NULL;
		}
	}
	free(to_export);
	return (0);
}

int	ft_prev_envp(t_token *shlvl, t_data *data)
{
	t_token	*tmp;
	char	*new;

	while (shlvl && shlvl->shlvl == data->shlvl)
	{
		if (shlvl->cmd_env == 0)
			ft_unset_prev(shlvl->data, data);
		else if (shlvl->cmd_env == 1)
			ft_export_prev(shlvl->data, shlvl, data);
		shlvl = shlvl->next;
	}
	data->shlvl--;
	new = ft_strjoin("SHLVL=", ft_itoa(data->shlvl));
	browse_data_var(new, data);
	tmp = shlvl;
	while (tmp && tmp->shlvl == data->shlvl)
	{
		if (tmp->cmd_env == 0)
			if (browse_data_var(tmp->data, data) == 1)
				add_var_envp(tmp->data, data);
		tmp = tmp->next;
	}
	free (new);
	return (0);
}

int	upgrade_shlvl(t_data *data)
{
	char	*shlvl;

	data->shlvl++;
	shlvl = ft_strjoin("SHLVL=", ft_itoa(data->shlvl));
	browse_data_var(shlvl, data);
	return (0);
}
