/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:53:33 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/10 11:33:26 by cdaveux          ###   ########.fr       */
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
	int		i;
	int		j;

	i = 0;
	while (data->envp[i])
	{
		j = 0;
		while (str[j] == data->envp[i][j] && (str[j] != '=' || str[j] != '+'))
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
			data->envp[i] = join_elems(data->envp[i], ft_strrchr(str, str[j + 2]));
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_assign(char *assignment)
{
	int	i;
	int	vrai;

	i = 1;
	vrai = 0;
	if (!ft_isalpha(assignment[0]) && assignment[0] != '_')
		return (1);
	if (assignment[0] == '_')
		vrai = 1;
	while (assignment[i] && assignment[i] != '=' && assignment[i] != '+')
	{
		if (!ft_isalnum(assignment[i]) && assignment[i] != '_')
			return (1);
		if (assignment[i] == '_' || ft_isdigit(assignment[i]))
			vrai = 1;
		i++;
	}
	if (assignment[i] == '+')
	{
		if (assignment[i + 1] != '=')
			return (1);
	}
	if (vrai == 1 && assignment[i] != '=' && assignment[i] != '+')
		return (1);
	return (0);
}

int	ft_export(t_token *token, t_data *data)
{
	t_token	*tmp;
	char	*trim;
	int		ret;

	tmp = token;
	ret = 0;
	while (tmp)
	{
		if (check_assign(tmp->data) == 0)
		{
			if (browse_data_var(tmp->data, data) == 1)
			{
				trim = ft_strtrimone(tmp->data, '+');printf("%s\n", trim);
				if (!trim)
					add_var_envp(tmp->data, data);
				else
					add_var_envp(trim, data);
				free(trim);
			}
		}
		else
			ret = 1;
		tmp = tmp->next;
	}
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
	return (0);
}
