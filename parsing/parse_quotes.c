/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:08:38 by cdaveux           #+#    #+#             */
/*   Updated: 2022/06/02 13:50:08 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_op(char *str, char op)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == op)
			return (1);
	}
	return (0);
}

int	no_data(t_token **new_token, int i, char *str)
{
	if (i > 1 && !(*new_token)->data)
	{
		(*new_token)->data = ft_create_data(str, i);
		return (1);
	}
	return (0);
}

int	ft_join(char *str, t_token **to_join, t_data *data)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strncmp(str, "$?", 2))
	{
		tmp = ft_itoa(data->exit_status);
		(*to_join)->data = join_elems((*to_join)->data, tmp);
		free(tmp);
		return (2);
	}
	else
		(*to_join)->data = join_elems((*to_join)->data,
				ft_search_env(&str[1], data));
	return (1 + ft_name(&str[1]));
}

int	dollar_in_quotes(t_token **new_token, char *str, char op, t_data *data)
{
	int		i;
	int		diff;

	i = 1;
	diff = 1;
	while (str[i] != op)
	{
		if (str[i] == '$' && (ft_search_env(&str[i + 1], data)
				|| !ft_strncmp(&str[i], "$?", 2)))
		{
			if (!no_data(&(*new_token), i, str) && diff != i)
				(*new_token)->data = ft_dup((*new_token)->data, i, diff, str);
			i += ft_join(&str[i], new_token, data);
			diff = i;
		}
		else
			i++;
	}
	if (!no_data(&(*new_token), i, str) && diff != i)
		(*new_token)->data = ft_dup((*new_token)->data, i, diff, str);
	return (i);
}

t_token	*fill_data_quotes(t_type token, char *str, char op, t_data *data)
{
	t_token	*new_token;
	int		i;

	new_token = NULL;
	if (!find_op(&str[1], op))
		return (NULL);
	new_token = ft_create_token(token);
	if (token == DOUBLE_QUOTE)
		i = dollar_in_quotes(&new_token, str, op, data);
	else
	{
		i = ft_strlen(&str[1]);
		new_token->data = ft_create_data(str, i);
	}
	new_token->data_size = i + 1;
	return (new_token);
}
