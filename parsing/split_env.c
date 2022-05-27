/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:49:25 by cdaveux           #+#    #+#             */
/*   Updated: 2022/05/27 16:21:21 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\f' || str[i] == 32)
			return (1);
	}
	return (0);
}

int	ft_len(char **str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
		len++;
	return (len);
}

t_token	*split_env(t_token *new_token, char *op, t_data *data)
{
	char	*tmp;
	char	**spaceless;
	int		i;

	i = 0;
	tmp = ft_strdup((const char *)ft_search_env(&op[1], data));
	if (!check_spaces(tmp))
	{
		new_token->data = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		spaceless = ft_split_bis(tmp, "\t\v\n\r\f ");
		free(tmp);
		tmp = NULL;
		while (spaceless[i])
		{
			if (i > 0)
			{
				tmp = ft_strdup(new_token->data);
				free(new_token->data);
			}
			new_token->data = ft_strjoin(tmp, spaceless[i]);
			free(tmp);
			if (i < ft_len(spaceless) - 1)
			{
				tmp = ft_strdup(new_token->data);
				free(new_token->data);
				new_token->data = ft_strjoin(tmp, " ");
				free(tmp);
			}
			i++;
		}
		i = -1;
		while (spaceless[++i])
			free(spaceless[i]);
		free(spaceless);
	}
	new_token->data_size = ft_name(&op[1]) + 1;
	return (new_token);
}
