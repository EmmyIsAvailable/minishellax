/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:08:38 by cdaveux           #+#    #+#             */
/*   Updated: 2022/05/30 16:35:47 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_create_data(char *str, int i)
{
	char	*data;
	int		j;

	j = 0;
	data = malloc(sizeof(char) * (i));
	if (!data)
		return (NULL);
	while (str[++j] && j < i)
		data[j - 1] = str[j];
	data[i - 1] = '\0';
	return (data);
}

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

int	dollar_in_quotes(t_token **new_token, char *str, char op, t_data *data)
{
	int		i;
	int		diff;

	i = 1;
	diff = 1;
	while (str[i] != op)
	{
		if (str[i] == '$' && ft_search_env(&str[i + 1], data))
		{
			if (!no_data(&(*new_token), i, str) && diff != i)
				(*new_token)->data = ft_dup((*new_token)->data, i, diff, str);
			(*new_token)->data = join_elems((*new_token)->data,
					ft_search_env(&str[i + 1], data));
			i += (1 + ft_name(&str[i + 1]));
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
