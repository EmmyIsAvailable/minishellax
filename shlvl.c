/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:51:55 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/27 15:28:17 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_export_prev(char *str, t_token *shlvl, t_data *data)
{
	t_token	*tmp;

	tmp = shlvl;
	while (tmp)
	{
		if (tmp->cmd_env == 0 && (int)ft_strlen(str) == ft_name(tmp->data))
		{
			if (ft_strncmp(tmp->data, str, ft_strlen(str)) == 0)
			{
				ft_export(tmp, data);
				break ;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_exec_unset_prev(char *to_export, char **envp)
{
	int	i;

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
}

int	ft_unset_prev(char *str, t_data *data)
{
	int		i;
	char	**envp;
	char	*to_export;
	int		lenght;

	i = 0;
	lenght = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '=')
			lenght = ft_name(str);
		i++;
	}
	i = -1;
	to_export = (char *)malloc(sizeof(char) * (lenght + 1));
	if (!to_export)
		return (1);
	while (str[++i] && i < lenght)
		to_export[i] = str[i];
	to_export[i] = '\0';
	envp = data->envp;
	ft_exec_unset_prev(to_export, envp);
	free(to_export);
	return (0);
}

int	ft_prev_envp(t_token **shlvl, t_data *data)
{
	t_token	*tmp;
	t_token	*tmp2;

	while ((*shlvl) && (*shlvl)->shlvl == data->shlvl)
	{
		if ((*shlvl)->cmd_env == 0)
			ft_unset_prev((*shlvl)->data, data);
		else if ((*shlvl)->cmd_env == 1)
			ft_export_prev((*shlvl)->data, *shlvl, data);
		ft_free(shlvl);
	}
	change_shlvl(data, '-');
	tmp = *shlvl;
	tmp2 = *shlvl;
	return (ft_prev_envp_bis(tmp, tmp2, data));
}

int	ft_prev_envp_bis(t_token *tmp, t_token *tmp2, t_data *data)
{
	while (tmp && tmp->shlvl == data->shlvl)
	{
		if (tmp->cmd_env == 0)
			if (browse_data_var(tmp->data, data) == 1)
				add_var_envp(tmp->data, data);
		tmp = tmp->next;
	}
	while (tmp2 && tmp2->shlvl == data->shlvl)
	{
		if (tmp2->cmd_env == 1)
			ft_unset(tmp2, data);
		tmp2 = tmp2->next;
	}
	return (0);
}
