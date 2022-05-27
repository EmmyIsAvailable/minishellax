/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:53:33 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/27 15:59:08 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
				trim = ft_strtrimone(tmp->data, '+');
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
