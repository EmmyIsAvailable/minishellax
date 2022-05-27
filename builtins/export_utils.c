/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:58:39 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/27 16:10:20 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**clean_envp(t_data *data)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = -1;
	tmp = NULL;
	while (data->envp[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	while (data->envp[++j])
		tmp[j] = ft_strdup(data->envp[j]);
	tmp[j] = NULL;
	free_tab(data->envp);
	data->envp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!data->envp)
		return (NULL);
	return (tmp);
}

int	add_var_envp(char *str, t_data *data)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = clean_envp(data);
	while (tmp[i])
	{
		data->envp[i] = ft_strdup(tmp[i]);
		if (!data->envp[i])
			return (1);
		i++;
	}
	data->envp[i] = ft_strdup(str);
	if (!data->envp[i])
		return (1);
	data->envp[i + 1] = NULL;
	free_tab(tmp);
	return (0);
}

int	browse_data_var(char *str, t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->envp[++i])
	{
		j = 0;
		while (str[j] == data->envp[i][j] && (str[j] != '=' && str[j] != '+'))
			j++;
		if (str[j] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(str);
			if (!data->envp[i])
				return (1);
			return (0);
		}
		if (str[j] == '+' && str[j + 1] == '=')
		{
			data->envp[i] = join_elems(data->envp[i],
					ft_strrchr(str, str[j + 2]));
			return (0);
		}
	}
	return (1);
}

int	check_assign(char *assignment)
{
	int	i;

	i = 1;
	if (!ft_isalpha(assignment[0]) && assignment[0] != '_')
		return (1);
	while (assignment[i] && assignment[i] != '=' && assignment[i] != '+')
	{
		if (!ft_isalnum(assignment[i]) && assignment[i] != '_')
			return (1);
		i++;
	}
	if (assignment[i] == '+')
	{
		if (assignment[i + 1] != '=')
			return (1);
	}
	else if (assignment[i] != '=')
		return (1);
	return (0);
}
