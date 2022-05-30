/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:49:25 by cdaveux           #+#    #+#             */
/*   Updated: 2022/05/30 17:24:03 by cdaveux          ###   ########.fr       */
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
	char	**spaceless;
	int		i;
	int		len;

	i = -1;
	len = 0;
	spaceless = NULL;
	if (!check_spaces(ft_search_env(&op[1], data)))
		new_token->data = join_elems(new_token->data, ft_search_env(&op[1], data));
	else
	{
		spaceless = ft_split_bis(ft_search_env(&op[1], data), "\t\v\n\r\f ");
		len = ft_len(spaceless);
		while (spaceless[++i])
		{
			new_token->data = join_elems(new_token->data, spaceless[i]);
			if (i < len - 1)
				new_token->data = join_elems(new_token->data, " ");
			free(spaceless[i]);
		}
		free(spaceless);
	}
	new_token->data_size = ft_name(&op[1]) + 1;
	return (new_token);
}
