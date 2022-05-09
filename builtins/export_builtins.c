/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:53:33 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/05 11:23:09 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_var_envp(char *str, t_data *data)
{
	int		i;
	char	**envp;

	i = 0;
	envp = data->envp;
	while (envp[i])
		i++;
	data->envp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!data->envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
			return (1);
		i++;
	}
	data->envp[i] = ft_strdup(str);
	if (!data->envp[i])
		return (1);
	data->envp[i + 1] = NULL;
	return (0);
}

int	browse_data_var(char *str, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->envp[i])
	{
		j = 0;
		while (str[j] == data->envp[i][j] && str[j] != '=')
			j++;
		if (str[j] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(str);
			if (!data->envp[i])
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_assign(char *assignment)
{
	int	i;
	int	eq_sign;

	i = 0;
	eq_sign = 0;
	if (ft_isalpha(assignment[i]) == 0 && assignment[i] != '_')
		return (1);
	while (assignment[++i])
	{
		if (assignment[i] == '=')
			eq_sign = 1;
	}
	if (eq_sign != 1)
		return (1);
	return (0);
}

int	ft_export(t_heads **line, t_data *data)
{
	t_token	*tmp;
	int		ret;

	tmp = (*line)->cmd;
	ret = 0;
	while (tmp)
	{
		if (check_assign(tmp->data) == 0)
		{
			if (browse_data_var(tmp->data, data) == 1)
				add_var_envp(tmp->data, data);
		}
		else
			ret = 1;
		tmp = tmp->next;
	}
	clear_all_heads(&(*line));
	return (ret);
}

int	ft_solo_export(t_data *data)
{
	char	**tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	tmp = ft_sort_tab(data->envp);
	while (tmp[i])
	{
		j = ft_strlen(tmp[i]);
		k = ft_name(tmp[i]) + 1;
		write(1, "declare -x ", 11);
		write(1, tmp[i], k);
		write(1, "\"", 1);
		while (k < j)
		{
			write(1, &tmp[i][k], 1);
			k++;
		}
		write(1, "\"\n", 2);
		i++;
	}
	printf("%s\n", (char *) NULL);
	return (0);
}
