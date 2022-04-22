/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:08:38 by cdaveux           #+#    #+#             */
/*   Updated: 2022/04/22 11:08:41 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_name(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (i);
	}
	return (i);
}

char	*ft_search_env(char *params, t_data *data)
{
	char	**envp;
	int		i;

	i = -1;
	envp = data->envp;
	while (envp[++i])
	{
		if (ft_strncmp(&envp[i][ft_name(params)], "=", 1) == 0)
		{
			if (ft_strncmp(envp[i], params, ft_name(params)) == 0)
				return (&envp[i][ft_name(params) + 1]);
		}
	}
	return (NULL);
}

char	*ft_dup(char *data, int i, int diff, char *str)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = malloc(sizeof(char) * (i - diff + 1));
	if (!tmp)
		return (NULL);
	while (j < i - diff)
	{
		tmp[j] = str[diff + j];
		j++;
	}
	tmp[j] = '\0';
	data = ft_strjoin(data, tmp);
	free(tmp);
	tmp = NULL;
	return (data);
}

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

t_token	*fill_data_quotes(token_type token, char *str, char op, t_data *data)
{
	t_token	*new_token;
	int		i;
	int		diff;

	i = 1;
	diff = 1;
	new_token = NULL;
	if (!find_op(&str[1], op))
		return (NULL);
	new_token = ft_create_token(token);
	while (str[i] != op)
	{
		if (str[i] == '$' && token == DOUBLE_QUOTE
			&& ft_search_env(&str[i + 1], data))
		{
			if (i > 1 && !new_token->data)
				new_token->data = ft_create_data(str, i);
			else if (diff != i)
				new_token->data = ft_dup(new_token->data, i, diff, str);
			new_token->data = ft_strjoin(new_token->data,
					(const char *)ft_search_env(&str[i + 1], data));
			i += (1 + ft_name(&str[i + 1]));
			diff = i;
		}
		else
			i++;
	}
	if (!new_token->data)
		new_token->data = ft_create_data(str, i);
	else if (diff != i)
		new_token->data = ft_dup(new_token->data, i, diff, str);
	new_token->data_size = i + 1;
	return (new_token);
}
