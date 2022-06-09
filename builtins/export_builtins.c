/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:53:33 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/09 16:54:25 by eruellan         ###   ########.fr       */
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

char	*ft_caps_value(char *tmp)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while(tmp[i] != '=')
		i++;
	ret = (char *)malloc(sizeof(char) * i + 2);
	i = 0;
	while (tmp[i] != '=')
	{
		ret[i] = tmp[i];
		i++;
	}
	ret[i] = '=';
	ret[i + 1] = '\0';
	return (ret);
}

int	ft_solo_export(t_heads **line, t_data *data)
{
	char	*export;
	char	**tmp;
	int		i;
	char	*tmp_var;
//	int		j;
//	int		k;

	i = 0;
	export = NULL;
	tmp = ft_sort_tab(data->envp);
	while (tmp[i])
	{
	//	j = ft_strlen(tmp[i]);
	//	k = ft_name(tmp[i]) + 1;
		tmp_var = ft_caps_value(tmp[i]);
		ft_strjoin(export, "declare -x ");
		ft_strjoin(export, tmp_var);
		ft_strjoin(export, "\"");
		ft_strjoin(export, ft_value(data, tmp_var));
		ft_strjoin(export, "\"");
		free(tmp_var);
/*		write(1, "declare -x ", 11);
		write(1, tmp[i], k);
		write(1, "\"", 1);
		while (k < j)
		{
			write(1, &tmp[i][k], 1);
			k++;
		}
		write(1, "\"\n", 2);*/
		i++;
	}
	write_outfile(line, export);
	free(export);
	return (0);
}
